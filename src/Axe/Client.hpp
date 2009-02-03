#	pragma once

#	include "ClientConnectResponse.hpp"
#	include "RouterConnection.hpp"

namespace Axe
{
	class Client
		: virtual public Shared
	{
	public:
		Client();

	public:
		void connect( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _login, const std::string & _password, const ClientConnectResponsePtr & _client );
		void run();

	protected:
		boost::asio::io_service m_service;
		RouterConnectionPtr m_router;
		ClientConnectResponsePtr m_response;
	};

	typedef AxeHandle<Client> ReceptionPtr;
}