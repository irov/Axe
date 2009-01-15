#	pragma once

namespace protocol_session_manager
{
	class proxy;
}

class client;
class router_connection;

class reception
{
public:
	reception();

public:
	void connect( const std::string & _login, const std::string & _password, const boost::asio::ip::tcp::endpoint & _endpoint, client * _cl );

	void run();

protected:
	boost::asio::io_service m_service;
	router_connection * m_router;

	protocol_session_manager::proxy * m_session_manager;
};