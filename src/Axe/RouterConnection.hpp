#	pragma once

#	include "AdapterConnection.hpp"
#	include "ConnectionCache.hpp"
#	include "ClientConnectResponse.hpp"

namespace Axe
{
	typedef AxeHandle<class Client> ClientPtr;

	class RouterConnection
		: public AdapterConnection
	{
	public:
		RouterConnection( boost::asio::io_service & _service, const ConnectionCachePtr & _connectionCache, const ClientConnectResponsePtr & _connectResponse );

	public:
		void createSession( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _login, const std::string & _password );

	public:
		ConnectionPtr createProxyConnection( std::size_t _endpointId );

	protected:
		void connectionSuccessful( ArchiveRead & _ar, std::size_t _size ) override;
		void connectionFailed( ArchiveRead & _ar, std::size_t _size ) override;

	protected:
		ClientConnectResponsePtr m_connectResponse;		
	};

	typedef AxeHandle<RouterConnection> RouterConnectionPtr;
}