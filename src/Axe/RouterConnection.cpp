#	include "pch.hpp"

#	include "RouterConnection.hpp"
#	include "RouterProxyConnection.hpp"

#	include "Response.hpp"

#	include "ArchiveRead.hpp"
#	include "ArchiveWrite.hpp"

#	include "Client.hpp"

#	include <AxeProtocols/Player.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	RouterConnection::RouterConnection( boost::asio::io_service & _service, const ConnectionCachePtr & _connectionCache, const ClientConnectResponsePtr & _connectResponse )
		: AdapterConnection( _service, _connectionCache, 0 )
		, m_connectResponse( _connectResponse )
	{		
	}
	//////////////////////////////////////////////////////////////////////////
	void RouterConnection::createSession( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _login, const std::string & _password )
	{
		ArchiveWrite & ar = this->connect( _endpoint );

		ar.writeString( _login );
		ar.writeString( _password );

		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	ConnectionPtr RouterConnection::createProxyConnection( std::size_t _endpointId )
	{
		RouterProxyConnectionPtr cn = new RouterProxyConnection( this, _endpointId );

		return cn;
	}
	//////////////////////////////////////////////////////////////////////////
	void RouterConnection::connectionSuccessful( ArchiveRead & _ar, std::size_t _size )
	{
		Proxy_PlayerPtr proxy = makeProxy<Proxy_Player>( _ar, m_connectionCache );

		m_connectResponse->connectSuccessful( proxy );
	}
	void RouterConnection::connectionFailed( ArchiveRead & _ar, std::size_t _size )
	{
		m_connectResponse->connectFailed();
	}

}