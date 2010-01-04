#	include "pch.hpp"

#	include <Axe/RouterConnection.hpp>
#	include <Axe/RouterProxyConnection.hpp>

#	include <Axe/Response.hpp>

#	include <Axe/ArchiveDispatcher.hpp>
#	include <Axe/ArchiveInvocation.hpp>

#	include <Axe/Client.hpp>

#	include <AxeProtocols/SessionManager.hpp>

namespace Axe
{
	const std::size_t router_endpoint_id = 0;
	//////////////////////////////////////////////////////////////////////////
	RouterConnection::RouterConnection( boost::asio::io_service & _service, const EndpointCachePtr & _endpointCache, const ConnectionCachePtr & _connectionCache, const ClientConnectResponsePtr & _connectResponse )
		: AdapterConnection( _service, router_endpoint_id, _endpointCache, _connectionCache )
		, m_connectResponse( _connectResponse )
	{		
	}
	//////////////////////////////////////////////////////////////////////////
	void RouterConnection::createSession( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _login, const std::string & _password )
	{
		m_connectionCache->addConnection( router_endpoint_id, this );

		ArchiveInvocation & permission = this->connect( _endpoint );

		permission.writeString( _login );
		permission.writeString( _password );
	}
	//////////////////////////////////////////////////////////////////////////
	ConnectionPtr RouterConnection::createProxyConnection( std::size_t _hostId )
	{
		RouterProxyConnectionPtr cn = new RouterProxyConnection( this, _hostId );

		return cn;
	}
	//////////////////////////////////////////////////////////////////////////
	void RouterConnection::connectionSuccessful( ArchiveDispatcher & _ar, std::size_t _size )
	{
		Proxy_SessionPtr proxy = makeProxy<Proxy_SessionPtr>( _ar );

		m_connectResponse->connectSuccessful( proxy );
	}
	//////////////////////////////////////////////////////////////////////////
	void RouterConnection::connectionFailed( ArchiveDispatcher & _ar, std::size_t _size )
	{
		m_connectResponse->connectFailed();
	}

}