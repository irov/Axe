#	include "pch.hpp"

#	include "reception.hpp"

#	include "router_connection.hpp"

#	include "client.hpp"

#	include "protocols/protocol_session_manager.hpp"

reception::reception()
: m_router(0)
{
}

class MySessionManagerCreateResponse
	: public protocol_session_manager::response_create
{
public:
	MySessionManagerCreateResponse( client * _cl )
		: m_client(_cl)
	{

	}
public:
	void response( std::size_t _id ) override
	{
		m_client->on_connect( _id );
	}

protected:
	client * m_client;
};

void reception::connect( const std::string & _login, const std::string & _password, const boost::asio::ip::tcp::endpoint & _endpoint, client * _cl )
{
	m_router = new router_connection( m_service );

	m_router->connect( _endpoint );

	protocol_grid::proxy * grid = new protocol_grid::proxy( 0, m_router );

	m_session_manager = new protocol_session_manager::proxy( 0, m_router );
	m_session_manager->create_async( _login, _password, new MySessionManagerCreateResponse( _cl )  );
}

void reception::run()
{
	m_service.run();
}
