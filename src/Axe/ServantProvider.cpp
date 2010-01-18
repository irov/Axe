#	include "pch.hpp"

#	include "ServantProvider.hpp"
#	include "ServantFactory.hpp"

#	include <AxeProtocols/EvictorManager.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	ServantProvider::ServantProvider( const ServantFactoryPtr & _servantFactory, const Proxy_EvictorManagerPtr & _evictorManager )
		: m_servantFactory(_servantFactory)
		, m_evictorManager(_evictorManager)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void ServantProvider::get( std::size_t _servantId, std::size_t _adapterId, const ServantProviderResponsePtr & _cb )
	{
		TMapWantedServant::iterator it_found = m_wantedServant.find( _servantId );

		if( it_found == m_wantedServant.end() )
		{
			m_evictorManager->get_async( 
				bindResponse( boost::bind( &ServantProvider::onGet, handlePtr(this), _1, _2, _servantId )
					, boost::bind( &ServantProvider::onException, handlePtr(this), _1, _servantId ) ) 
				, _servantId
				, _adapterId
				);

			TListServantProviderResponse responses;
			responses.push_back( _cb );

			it_found = m_wantedServant.insert( std::make_pair(_servantId, responses) ).first;
		}

		it_found->second.push_back( _cb );
	}
	//////////////////////////////////////////////////////////////////////////
	void ServantProvider::onGet( const AxeUtil::Archive & _data, std::size_t _typeId, std::size_t _servantId )
	{
		ServantPtr servant = m_servantFactory->genServantWithId( _typeId );

		
		// TODO

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
		catch( const Axe::EvictingAlreadyRestored & _restored )
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
		catch( const Axe::EvictingNotFoundException & _notfound )
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