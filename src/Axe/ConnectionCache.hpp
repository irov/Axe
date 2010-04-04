#	pragma once

#	include <AxeUtil/Shared.hpp>

#	include <map>

namespace Axe
{
	typedef AxeHandle<class Connection> ConnectionPtr;
	typedef AxeHandle<class ServantConnection> ServantConnectionPtr;
	typedef AxeHandle<class ProxyConnectionProvider> ProxyConnectionProviderPtr;


	class ConnectionProvider
		: virtual public AxeUtil::Shared
	{
	public:
		virtual ConnectionPtr createAdapterConnection( std::size_t _adapterId ) = 0;
		virtual ServantConnectionPtr createServantConnection( const std::string & _name, const boost::asio::ip::tcp::endpoint & _endpoint ) = 0;
	};

	typedef AxeHandle<ConnectionProvider> ConnectionProviderPtr;

	class ConnectionCache
		: virtual public AxeUtil::Shared
	{
	public:
		ConnectionCache( const ConnectionProviderPtr & _provider );

	public:
		void addAdapterConnection( std::size_t _adapterId, const ConnectionPtr & _connection );
		const ConnectionPtr & getAdapterConnection( std::size_t _adapterId );
		const ServantConnectionPtr & getServantConnection( const std::string & _name, const boost::asio::ip::tcp::endpoint & _endpoint );

		const ProxyConnectionProviderPtr & getProxyAdapterProvider( std::size_t _servantId, std::size_t _adapterId ); 
		const ProxyConnectionProviderPtr & getProxyServantProvider( const std::string & _name, const boost::asio::ip::tcp::endpoint & _endpoint );

	public:
		void relocateProxy( std::size_t _servantId, std::size_t _adapterId );

	protected:
		ConnectionProviderPtr m_provider;

		typedef std::map<std::size_t, ConnectionPtr> TMapAdapterConnections;
		TMapAdapterConnections m_adapterConnections;

		typedef std::map<std::string, ServantConnectionPtr> TMapServantConnections;
		TMapServantConnections m_servantConnections;

		typedef std::map<std::size_t, ProxyConnectionProviderPtr> TMapProxyAdapterProviders;
		TMapProxyAdapterProviders m_proxyAdapterProviders;

		typedef std::map<std::string, ProxyConnectionProviderPtr> TMapProxyServantProviders;
		TMapProxyServantProviders m_proxyServantProviders;
	};

	typedef AxeHandle<ConnectionCache> ConnectionCachePtr;
}