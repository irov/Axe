#	pragma once

#	include "Shared.hpp"

namespace Axe
{
	typedef AxeHandle<class Connection> ConnectionPtr;

	class ConnectionProvider
		: virtual public Shared
	{
	public:
		virtual ConnectionPtr createConnection( std::size_t _endpointId ) = 0;
	};

	typedef AxeHandle<ConnectionProvider> ConnectionProviderPtr;


	class ConnectionCache
		: virtual public Shared
	{
	public:
		ConnectionCache( const ConnectionProviderPtr & _provider );

	public:
		const ConnectionPtr & getConnection( std::size_t _endpointId );

	protected:
		typedef std::map<std::size_t, ConnectionPtr> TMapConnections;
		TMapConnections m_connections;

		ConnectionProviderPtr m_provider;
	};

	typedef AxeHandle<ConnectionCache> ConnectionCachePtr;
}