#	pragma once

#	include <Axe/Shared.hpp>

namespace Axe
{
	typedef AxeHandle<class Connection> ConnectionPtr;
	typedef AxeHandle<class ConnectionCache> ConnectionCachePtr;


	class ConnectionProvider
		: virtual public Shared
	{
	public:
		virtual ConnectionPtr createConnection( std::size_t _hostId, const ConnectionCachePtr & _connectionCache ) = 0;
	};

	typedef AxeHandle<ConnectionProvider> ConnectionProviderPtr;

	class ConnectionCache
		: virtual public Shared
	{
	public:
		ConnectionCache( const ConnectionProviderPtr & _provider );

	public:
		void addConnection( std::size_t _hostId, const ConnectionPtr & _connection );
		const ConnectionPtr & getConnection( std::size_t _hostId );

	protected:
		typedef std::map<std::size_t, ConnectionPtr> TMapConnections;
		TMapConnections m_connections;

		ConnectionProviderPtr m_provider;
	};

	typedef AxeHandle<ConnectionCache> ConnectionCachePtr;
}