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
	RouterConnection::RouterConnection( boost::asio::io_service & _service )
		: AdapterConnection( _service, m_connectionCache )
	{

	}
	//////////////////////////////////////////////////////////////////////////
	void RouterConnection::createSession( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _login, const std::string & _password, const ClientPtr & _client )
	{
		m_clientResponse = _client;

		ArchiveWrite & ar = this->connect( _endpoint );

		ar.writeString( _login );
		ar.writeString( _password );

		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void RouterConnection::connectionSuccessful( ArchiveRead & _ar, std::size_t _size )
	{
		Proxy_PlayerPtr proxy = makeProxy<Proxy_Player>( _ar, m_connectionCache );

		_client->connectSuccessful( proxy );
	}
	void RouterConnection::connectionFailed( ArchiveRead & _ar, std::size_t _size )
	{
		_client->connectFailed();
	}
	//////////////////////////////////////////////////////////////////////////
	ConnectionPtr RouterConnection::createConnection( std::size_t _endpointId )
	{
		RouterProxyConnectionPtr cn = new RouterProxyConnection( this, _endpointId );

		return cn;
	}
}