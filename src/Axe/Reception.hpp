#	pragma once

#	include "RouterConnection.hpp"

namespace Axe
{
	typedef AxeHandle<class Client> ClientPtr;

	class Reception
		:	public Shared
	{
	public:
		Reception();

	public:
		void connect( const std::string & _login, const std::string & _password, const boost::asio::ip::tcp::endpoint & _endpoint, const ClientPtr & _client );
		void run();

	protected:
		boost::asio::io_service m_service;
		RouterConnectionPtr m_router;
	};

	typedef AxeHandle<Reception> ReceptionPtr;
}