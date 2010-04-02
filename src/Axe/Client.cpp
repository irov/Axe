#	include "pch.hpp"

#	include <Axe/Client.hpp>

#	include <Axe/RouterConnection.hpp>
#	include <Axe/Socket.hpp>

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
		SocketPtr socket = new Socket( m_service );

		m_routerConnection = new RouterConnection( socket, m_connectionCache, 0, _client );

		m_routerConnection->createSession( _endpoint, _login, _password );
	}
	//////////////////////////////////////////////////////////////////////////
	ConnectionPtr Client::createAdapterConnection( std::size_t _adapterId )
	{
		ConnectionPtr cn = m_routerConnection->createProxyConnection( _adapterId );

		return cn;
	}
	//////////////////////////////////////////////////////////////////////////
	void Client::run()
	{
		m_service.run();
	}
}