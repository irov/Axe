#	pragma once

#	include <AxeUtil/Shared.hpp>

#	include <map>

namespace Axe
{
	typedef AxeHandle<class Connection> ConnectionPtr;
	typedef AxeHandle<class ConnectionCache> ConnectionCachePtr;
	typedef AxeHandle<class ProxyHostProvider> ProxyHostProviderPtr;


	class ConnectionProvider
		: virtual public AxeUtil::Shared
	{
	public:
		virtual ConnectionPtr createConnection( std::size_t _hostId ) = 0;
	};

	typedef AxeHandle<ConnectionProvider> ConnectionProviderPtr;


	class ConnectionCache
		: virtual public AxeUtil::Shared
	{
	public:
		ConnectionCache( const ConnectionProviderPtr & _provider );

	public:
		void addConnection( std::size_t _hostId, const ConnectionPtr & _connection );
		const ConnectionPtr & getConnection( std::size_t _hostId );

		const ProxyHostProviderPtr & getProxyHostProvider( std::size_t _servantId, std::size_t _hostId ); 

	public:
		void relocateProxy( std::size_t _servantId, std::size_t _hostId );

	protected:
		typedef std::map<std::size_t, ConnectionPtr> TMapConnections;
		TMapConnections m_connections;

		ConnectionProviderPtr m_provider;

		typedef std::map<std::size_t, ProxyHostProviderPtr> TMapProxyHostProviders;
		TMapProxyHostProviders m_proxyHostProviders;
	};

	typedef AxeHandle<ConnectionCache> ConnectionCachePtr;
}