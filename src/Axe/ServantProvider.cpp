#	include "pch.hpp"

#	include "ServantProvider.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	void ServantProvider::get( std::size_t _servantId, const ServantProviderResponsePtr & _cb )
	{
		TMapWantedServant::iterator it_found = m_wantedServant.find( _servantId );

		if( it_found == m_wantedServant.end() )
		{
			m_evictorManager->get_async( 
				bindResponse( boost::bind( &ServantProvider::onGet, handlePtr(this), _1, _servantId ) ) 
				, _servantId
				);

			TListServantProviderResponse responses;
			responses.push_back( _cb );

			it_found = m_wantedServant.insert( std::make_pair(_servantId, responses) ).first;
		}

		it_found->second.push_back( _cb );
	}
	//////////////////////////////////////////////////////////////////////////
	void ServantProvider::onGet( const AxeUtil::Archive & _data, std::size_t _servantId )
	{
		ServantPtr servant;

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
}