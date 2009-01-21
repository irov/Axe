#	include "pch.hpp"

#	include "Reception.hpp"
#	include "RouterConnection.hpp"
#	include "Client.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Reception::Reception()
		: m_router(0)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Reception::connect( const std::string & _login, const std::string & _password, const boost::asio::ip::tcp::endpoint & _endpoint, const ClientPtr & _client )
	{
		m_router = new RouterConnection( m_service );
		m_router->connect( _endpoint );

		m_router->createSession( _login, _password, _client )
	}
	//////////////////////////////////////////////////////////////////////////
	void Reception::run()
	{
		m_service.run();
	}
}