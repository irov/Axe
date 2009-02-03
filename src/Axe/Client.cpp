#	include "pch.hpp"

#	include "Client.hpp"
#	include "RouterConnection.hpp"
#	include "Client.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Client::Client()
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Client::connect( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _login, const std::string & _password, const ClientConnectResponsePtr & _client )
	{
		m_router = new RouterConnection( m_service,  );

		m_router->createSession( _endpoint, _login, _password, _client );
	}
	//////////////////////////////////////////////////////////////////////////
	void Client::run()
	{
		m_service.run();
	}
}