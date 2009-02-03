#	pragma once

#	include "AdapterConnection.hpp"
#	include "ConnectionCache.hpp"
#	include "ClientConnectResponse.hpp"

namespace Axe
{
	typedef AxeHandle<class Client> ClientPtr;

	class RouterConnection
		: public AdapterConnection
		, public ConnectionProvider
	{
	public:
		RouterConnection( boost::asio::io_service & _service );

	public:
		void createSession( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _login, const std::string & _password, const ClientConnectResponsePtr & _client );

	protected:
		ConnectionPtr createConnection( std::size_t _endpointId ) override;

	protected:
		void connectionSuccessful( ArchiveRead & _ar, std::size_t _size ) override;
		void connectionFailed( ArchiveRead & _ar, std::size_t _size ) override;

	protected:
		ClientConnectResponsePtr m_clientResponse;
		ConnectionCachePtr m_connectionCache;
	};

	typedef AxeHandle<RouterConnection> RouterConnectionPtr;
}