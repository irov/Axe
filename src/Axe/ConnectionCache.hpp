#	pragma once

#	include <AxeUtil/Shared.hpp>

#	include <map>

namespace Axe
{
	typedef AxeHandle<class Connection> ConnectionPtr;
	typedef AxeHandle<class ConnectionCache> ConnectionCachePtr;
	typedef AxeHandle<class ProxyAdapterProvider> ProxyAdapterProviderPtr;


	class ConnectionProvider
		: virtual public AxeUtil::Shared
	{
	public:
		virtual ConnectionPtr createConnection( std::size_t _adapterId ) = 0;
	};

	typedef AxeHandle<ConnectionProvider> ConnectionProviderPtr;


	class ConnectionCache
		: virtual public AxeUtil::Shared
	{
	public:
		ConnectionCache( const ConnectionProviderPtr & _provider );

	public:
		void addConnection( std::size_t _adapterId, const ConnectionPtr & _connection );
		const ConnectionPtr & getConnection( std::size_t _adapterId );

		const ProxyAdapterProviderPtr & getProxyAdapterProvider( std::size_t _servantId, std::size_t _adapterId ); 

	public:
		void relocateProxy( std::size_t _servantId, std::size_t _adapterId );

	protected:
		typedef std::map<std::size_t, ConnectionPtr> TMapConnections;
		TMapConnections m_connections;

		ConnectionProviderPtr m_provider;

		typedef std::map<std::size_t, ProxyAdapterProviderPtr> TMapProxyAdapterProviders;
		TMapProxyAdapterProviders m_proxyAdapterProviders;
	};

	typedef AxeHandle<ConnectionCache> ConnectionCachePtr;
}