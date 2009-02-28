#	include "pch.hpp"

#	include "Client.hpp"
#	include "RouterConnection.hpp"
#	include "Client.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Client::Client()
	{
		m_connectionCache = new ConnectionCache( this );
	}
	//////////////////////////////////////////////////////////////////////////
	void Client::connect( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _login, const std::string & _password, const ClientConnectResponsePtr & _client )
	{
		m_router = new RouterConnection( m_service, m_connectionCache, _client );

		m_router->createSession( _endpoint, _login, _password );
	}
	//////////////////////////////////////////////////////////////////////////
	ConnectionPtr Client::createConnection( std::size_t _hostId )
	{
		ConnectionPtr cn = m_router->createProxyConnection( _hostId );

		return cn;
	}
	//////////////////////////////////////////////////////////////////////////
	void Client::run()
	{
		m_service.run();
	}
}