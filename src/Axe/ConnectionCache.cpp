#	include "pch.hpp"

#	include "ConnectionCache.hpp"

#	include "Connection.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	ConnectionCache::ConnectionCache( const ConnectionProviderPtr & _provider )
		: m_provider(_provider)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void ConnectionCache::addConnection( std::size_t _hostId, const ConnectionPtr & _connection )
	{
		m_connections.insert( std::make_pair(_hostId, _connection) );
	}
	//////////////////////////////////////////////////////////////////////////
	const ConnectionPtr & ConnectionCache::getConnection( std::size_t _hostId )
	{
		TMapConnections::const_iterator it_found = m_connections.find( _hostId );

		if( it_found == m_connections.end() )
		{
			ConnectionPtr connection = m_provider->createConnection( _hostId, this );

			it_found = m_connections.insert( std::make_pair(_hostId, connection) ).first;
		}

		return it_found->second;
	}
}