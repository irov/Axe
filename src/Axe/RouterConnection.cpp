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
	static void s_connectionSuccessful( ArchiveDispatcher & _ar, std::size_t _size, const FRouterConnectionResponse & _response )
	{
		Proxy_SessionPtr proxy = makeProxy<Proxy_SessionPtr>( _ar );

		_response( proxy );
	}
	//////////////////////////////////////////////////////////////////////////
	void RouterConnection::createSession( 
		const boost::asio::ip::tcp::endpoint & _endpoint
		, const std::string & _login
		, const std::string & _password 
		, const const RouterConnectionResponsePtr & _cb
		)
	{
		m_connectionCache->addRouterConnection( _endpoint, this );

		ArchiveInvocation & permission = this->connect( 
			_endpoint
			, _cb
			);

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
	void RouterConnection::write( ArchiveInvocation & _ar ) const
	{
		char connectionTypeId = 2;
		_ar.writePOD( connectionTypeId );

		_ar.write( m_adapterId );
	}
}