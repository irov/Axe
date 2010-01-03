#	include "pch.hpp"

#	include <Axe/GridManager.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	GridManager::GridManager()
	{
		m_enumeratorID = 0;
	}
	//////////////////////////////////////////////////////////////////////////
	void GridManager::addAdapter( const Bellhop_GridManager_addAdapterPtr & _cb, const std::string & _name, const std::string & _endpoint )
	{
		TMapAdapterIds::const_iterator it_found = m_adapterIds.find( _name );

		if( it_found != m_adapterIds.end() )
		{
			AdapterAlreadyExistException ex;
			ex.name = _name;
			_cb->throw_exception( ex );
			return;
		}

		it_found = m_adapterIds.insert( std::make_pair(_name, ++m_enumeratorID) ).first;
		m_endpoints.insert( std::make_pair(m_enumeratorID, _endpoint) );

		_cb->response( it_found->second );
	}
	//////////////////////////////////////////////////////////////////////////
	void GridManager::getAdapterEndpoint( const Bellhop_GridManager_getAdapterEndpointPtr & _cb, std::size_t _hostId )
	{
		TMapEndpoints::const_iterator it_found = m_endpoints.find( _hostId );

		if( it_found == m_endpoints.end() )
		{
			HostNotFoundException ex;
			ex.hostId = _hostId;

			_cb->throw_exception( ex );
			return;
		}

		_cb->response( it_found->second );
	}
	//////////////////////////////////////////////////////////////////////////
	void GridManager::addUnique( const Bellhop_GridManager_addUniquePtr & _cb, const std::string & _name, const Proxy_UniquePtr & _unique )
	{
		TMapUniques::const_iterator it_found = m_uniques.find( _name );

		if( it_found != m_uniques.end() )
		{
			UniqueAlreadyExistException ex;
			ex.name = _name;

			_cb->throw_exception( ex );
			return;
		}

		m_uniques.insert( std::make_pair(_name, _unique) );
	
		_cb->response();
	}
	//////////////////////////////////////////////////////////////////////////
	void GridManager::getUnique( const Bellhop_GridManager_getUniquePtr & _cb, const std::string & _name )
	{
		TMapUniques::const_iterator it_found = m_uniques.find( _name );

		if( it_found == m_uniques.end() )
		{
			UniqueNotFoundException ex;
			ex.name = _name;
			_cb->throw_exception( ex );
			return;
		}

		_cb->response( it_found->second );
	}

}