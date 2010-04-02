#	pragma once

#	include <Axe/RouterConnection.hpp>
#	include <Axe/ConnectionCache.hpp>
#	include <Axe/ClientConnectResponse.hpp>

namespace Axe
{
	class Client
		: virtual public AxeUtil::Shared
		, public ConnectionProvider
	{
	public:
		Client();

	public:
		void connect( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _login, const std::string & _password, const ClientConnectResponsePtr & _client );
		void run();

	protected:
		ConnectionPtr createAdapterConnection( std::size_t _adapterId ) override;

	protected:
		boost::asio::io_service m_service;
		RouterConnectionPtr m_routerConnection;

		ConnectionCachePtr m_connectionCache;
		ClientConnectResponsePtr m_response;
	};

	typedef AxeHandle<Client> ClientPtr;
}