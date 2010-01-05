#	include "pch.hpp"

#	include "ServantFactory.hpp"

#	include <AxeProtocols/GridManager.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	ServantFactory::ServantFactory( const Proxy_GridManagerPtr & _gridManager )
		: m_gridManager(_gridManager)
	{

	}
	//////////////////////////////////////////////////////////////////////////
	void ServantFactory::getTypeId( const std::string & _type, const ServantFactoryGetIdResponsePtr & _cb )
	{
		TMapIdCache::iterator it_found = m_ids.find( _type );

		if( it_found != m_ids.end() )
		{
			_cb->onServantTypeId( it_found->second );
		}
		else
		{
			this->provideTypeId( _type, _cb );
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void ServantFactory::provideTypeId( const std::string & _type, const ServantFactoryGetIdResponsePtr & _cb )
	{
		TMapWantedResponse::iterator it_found = m_wantedIds.find( _type );

		if( it_found == m_wantedIds.end() )
		{
			TListWantedResponse responses;
		
			m_gridManager->getServantTypeId_async( 
				bindResponse( boost::bind( &ServantFactory::getTypeIdResponse, handlePtr(this), _1, _type ) )
				, _type 
				);

			it_found = m_wantedIds.insert( std::make_pair(_type, responses) ).first;
		}
		
		it_found->second.push_back( _cb );
	}
	//////////////////////////////////////////////////////////////////////////
	void ServantFactory::getTypeIdResponse( std::size_t _id, const std::string & _type )
	{
		m_ids.insert( std::make_pair( _type, _id ) );

		TMapWantedResponse::iterator it_found = m_wantedIds.find( _type );

		if( it_found == m_wantedIds.end() )
		{
			throw;
		}

		for( TListWantedResponse::iterator
			it = it_found->second.begin(),
			it_end = it_found->second.end();
		it != it_end;
		++it )
		{
			(*it)->onServantTypeId( _id );
		}
	}
}