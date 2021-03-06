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
		virtual ConnectionPtr createServantConnection( const std::string & _name, const boost::asio::ip::tcp::endpoint & _endpoint ) = 0;
		virtual ConnectionPtr createRouterConnection( const boost::asio::ip::tcp::endpoint & _endpoint ) = 0;
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

		void addServantConnection( const std::string & _name, const ConnectionPtr & _connection );
		const ConnectionPtr & getServantConnection( const std::string & _name, const boost::asio::ip::tcp::endpoint & _endpoint );

		void addRouterConnection( const boost::asio::ip::tcp::endpoint & _endpoint, const ConnectionPtr & _connection );
		const ConnectionPtr & getRouterConnection( const boost::asio::ip::tcp::endpoint & _endpoint );

		const ProxyConnectionProviderPtr & getProxyAdapterProvider( std::size_t _servantId, std::size_t _adapterId ); 
		const ProxyConnectionProviderPtr & getProxyServantProvider( const std::string & _name, const boost::asio::ip::tcp::endpoint & _endpoint );

	public:
		void relocateProxy( std::size_t _servantId, std::size_t _adapterId );

	protected:
		ConnectionProviderPtr m_provider;

		typedef std::map<std::size_t, ConnectionPtr> TMapAdapterConnections;
		TMapAdapterConnections m_adapterConnections;

		typedef std::map<std::string, ConnectionPtr> TMapServantConnections;
		TMapServantConnections m_servantConnections;

		typedef std::map<boost::asio::ip::tcp::endpoint, ConnectionPtr> TMapRouterConnections;
		TMapRouterConnections m_routerConnections;

		typedef std::map<std::size_t, ProxyConnectionProviderPtr> TMapProxyAdapterProviders;
		TMapProxyAdapterProviders m_proxyAdapterProviders;

		typedef std::map<std::string, ProxyConnectionProviderPtr> TMapProxyServantProviders;
		TMapProxyServantProviders m_proxyServantProviders;
	};

	typedef AxeHandle<ConnectionCache> ConnectionCachePtr;
}