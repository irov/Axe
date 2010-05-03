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
	//////////////////////////////////////////////////////////////////////////
	RouterConnection::RouterConnection( const SocketPtr & _socket, const ConnectionCachePtr & _connectionCache )
		: Connection(_socket, _connectionCache)
		, m_connectionCache(_connectionCache)
	{		
	}
	//////////////////////////////////////////////////////////////////////////
	void RouterConnection::createSession( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _login, const std::string & _password )
	{
		m_connectionCache->addRouterConnection( _endpoint, this );

		ArchiveInvocation & permission = this->connect( _endpoint );

		permission.writeString( _login );
		permission.writeString( _password );
	}
	//////////////////////////////////////////////////////////////////////////
	ConnectionPtr RouterConnection::createProxyConnection( std::size_t _adapterId )
	{
		RouterProxyConnectionPtr cn = new RouterProxyConnection( this, _adapterId );

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
	//////////////////////////////////////////////////////////////////////////
	void RouterConnection::write( ArchiveInvocation & _ar ) const
	{
		char connectionTypeId = 2;
		_ar.writePOD( connectionTypeId );

		_ar.write( m_adapterId );
	}
}