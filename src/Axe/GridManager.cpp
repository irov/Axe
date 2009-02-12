#	include "pch.hpp"

#	include "GridManager.hpp"

namespace Axe
{
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
}