#	pragma once

#	include "Shared.hpp"

namespace Axe
{
	typedef AxeHandle<class Connection> ConnectionPtr;

	class ConnectionProvider
	{
	public:
		virtual ConnectionPtr createConnection( std::size_t _endpointId ) = 0;
	};

	class ConnectionCache
		: public Shared
	{
	public:
		ConnectionCache( ConnectionProvider * _provider );

	public:
		const ConnectionPtr & getConnection( std::size_t _endpointId );

	protected:
		typedef std::map<std::size_t, ConnectionPtr> TMapConnections;
		TMapConnections m_connections;

		ConnectionProvider * m_provider;
	};

	typedef AxeHandle<ConnectionCache> ConnectionCachePtr;
}