#	include "pch.hpp"

#	include "GridManager.hpp"

namespace AxeLib
{
	//////////////////////////////////////////////////////////////////////////
	GridManager::GridManager()
	{
		m_adapterEnumerator = 0;
		m_servantTypeEnumerator = 0;
	}
	//////////////////////////////////////////////////////////////////////////
	void GridManager::addAdapter_async( const Bellhop_GridManager_addAdapterPtr & _cb, const std::string & _name, const std::string & _endpoint )
	{
		TMapAdapterIds::const_iterator it_found = m_adapterIds.find( _name );

		if( it_found != m_adapterIds.end() )
		{
			AdapterAlreadyExistException ex;
			ex.name = _name;
			_cb->throw_exception( ex );
			return;
		}

		it_found = m_adapterIds.insert( std::make_pair(_name, ++m_adapterEnumerator) ).first;
		m_endpoints.insert( std::make_pair(m_adapterEnumerator, _endpoint) );

		_cb->response( m_enumeratorID );
	}
	//////////////////////////////////////////////////////////////////////////
	void GridManager::getAdapterEndpoint_async( const Bellhop_GridManager_getAdapterEndpointPtr & _cb, std::size_t _hostId )
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
	void GridManager::addUnique_async( const Bellhop_GridManager_addUniquePtr & _cb, const std::string & _name, const ProxyPtr & _unique )
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
	void GridManager::getUnique_async( const Bellhop_GridManager_getUniquePtr & _cb, const std::string & _name )
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
	//////////////////////////////////////////////////////////////////////////
	void GridManager::getServantTypeId_async( const Bellhop_GridManager_getServantTypeIdPtr & _cb, const std::string & _type )
	{
		TMapServantTypeIds::iterator it_found = m_servantTypeIds.find( _type );

		if( it_found == m_servantTypeIds.end() )
		{
			it_found = m_servantTypeIds.insert( std::make_pair(_type, ++m_servantTypeEnumerator) ).first;
		}

		_cb->response( it_found->second );
	}
}