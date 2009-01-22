#	include "pch.hpp"

#	include "ConnectionCache.hpp"

#	include "Connection.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	ConnectionCache::ConnectionCache( ConnectionProvider * _provider )
		: m_provider(_provider)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	const ConnectionPtr & ConnectionCache::getConnection( std::size_t _endpointId )
	{
		TMapConnections::const_iterator it_found = m_connections.find( _endpointId );

		if( it_found == m_connections.end() )
		{
			ConnectionPtr connection = m_provider->createConnection( _endpointId );

			it_found = m_connections.insert( std::make_pair(_endpointId, connection) ).first;
		}

		return it_found->second;
	}
}