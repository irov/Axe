#	include "pch.hpp"

#	include "Reception.hpp"
#	include "RouterConnection.hpp"
#	include "Client.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Reception::Reception()
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Reception::connect( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _login, const std::string & _password, const ClientPtr & _client )
	{
		m_router = new RouterConnection( m_service );

		m_router->createSession( _endpoint, _login, _password, _client );
	}
	//////////////////////////////////////////////////////////////////////////
	void Reception::run()
	{
		m_service.run();
	}
}