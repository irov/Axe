#	include "pch.hpp"

#	include "GridManager.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	GridManager::GridManager( const Proxy_SessionManagerPtr & _sessionManager )
		: m_sessionManager(_sessionManager)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void GridManager::addAdapter( const Bellhop_GridManager_addAdapterPtr & _cb, const std::string & _name )
	{
		TMapAdapterIds::const_iterator it_found = m_adapterIds.find( _name );

		if( it_found == m_adapterIds.end() )
		{
			it_found = 
				m_adapterIds.insert( std::make_pair( _name, ++m_enumeratorID ) ).first;
		}

		_cb->response( it_found->second );
	}
	//////////////////////////////////////////////////////////////////////////
	void GridManager::getSessionManager( const Bellhop_GridManager_getSessionManagerPtr & _cb )
	{
		_cb->response( m_sessionManager );
	}
}