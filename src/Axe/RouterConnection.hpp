#	pragma once

#	include <Axe/AdapterConnection.hpp>
#	include <Axe/ConnectionCache.hpp>
#	include <Axe/ClientConnectResponse.hpp>

namespace Axe
{
	class RouterConnection
		: public AdapterConnection
	{
	public:
		RouterConnection( const SocketPtr & _socket, const ConnectionCachePtr & _connectionCache, const EndpointCachePtr & _endpointCache, const ClientConnectResponsePtr & _connectResponse );

	public:
		void createSession( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _login, const std::string & _password );

	public:
		ConnectionPtr createProxyConnection( std::size_t _adapterId );

	protected:
		void connectionSuccessful( ArchiveDispatcher & _ar, std::size_t _size ) override;
		void connectionFailed( ArchiveDispatcher & _ar, std::size_t _size ) override;

	protected:
		ConnectionCachePtr m_connectionCache;
		ClientConnectResponsePtr m_connectResponse;
	};

	typedef AxeHandle<RouterConnection> RouterConnectionPtr;
}