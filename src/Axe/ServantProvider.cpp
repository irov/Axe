#	include "pch.hpp"

#	include "ServantProvider.hpp"
#	include "ServantFactory.hpp"
#	include "Communicator.hpp"

#	include <AxeProtocols/EvictorManager.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	ServantProvider::ServantProvider( const CommunicatorPtr & _communicator, std::size_t _adapterId )
		: m_communicator(_communicator)
		, m_adapterId(_adapterId)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void ServantProvider::get( std::size_t _servantId, const ServantProviderResponsePtr & _cb )
	{
		TMapWantedServant::iterator it_found = m_wantedServant.find( _servantId );

		if( it_found == m_wantedServant.end() )
		{
			const Proxy_EvictorManagerPtr & evictorManager = 
				m_communicator->getEvictorManager();

			evictorManager->get_async(
				amiCallback( 
					amiMethod( this, &ServantProvider::onGet, _servantId ),
					amiMethod( this, &ServantProvider::onException, _servantId )					
					)
				, _servantId
				, m_adapterId
				);

			TListServantProviderResponse responses;
			responses.push_back( _cb );

			it_found = m_wantedServant.insert( std::make_pair(_servantId, responses) ).first;
		}

		it_found->second.push_back( _cb );
	}
	//////////////////////////////////////////////////////////////////////////
	void ServantProvider::onGet( const AxeUtil::Archive & _data, const std::string & _type, std::size_t _servantId )
	{
		const ServantFactoryPtr & servantFactory = 
			m_communicator->getServantFactory();

		ServantPtr servant = servantFactory->genServant( _type );
		
		const ConnectionCachePtr & connectionCache = m_communicator->getConnectionCache();
		
		ArchiveDispatcher ar( const_cast<AxeUtil::Archive &>(_data), connectionCache );

		const boost::property_tree::ptree & pr = m_communicator->getProperties();

		servant->restore( ar, pr );

		TMapWantedServant::iterator it_found = m_wantedServant.find( _servantId );

		for( TListServantProviderResponse::iterator
			it = it_found->second.begin(),
			it_end = it_found->second.end();
		it != it_end;
		++it )
		{
			(*it)->onServant( servant );
		}

		m_wantedServant.erase( it_found );
	}
	//////////////////////////////////////////////////////////////////////////
	void ServantProvider::onException( const Exception & _ex, std::size_t _servantId )
	{
		TMapWantedServant::iterator it_found = m_wantedServant.find( _servantId );

		try
		{
			_ex.rethrow();
		}
		catch( const Axe::EvictorAlreadyRestored & _restored )
		{
			for( TListServantProviderResponse::iterator
				it = it_found->second.begin(),
				it_end = it_found->second.end();
			it != it_end;
			++it )
			{
				(*it)->onServantReplace( _restored.adapterId );
			}
		}
		catch( const Axe::EvictorNotFoundException & _notfound )
		{
			for( TListServantProviderResponse::iterator
				it = it_found->second.begin(),
				it_end = it_found->second.end();
			it != it_end;
			++it )
			{
				(*it)->onServantNotFound( _notfound.servantId );
			}
		}

		m_wantedServant.erase( it_found );
	}
}