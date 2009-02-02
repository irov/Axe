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
		: AdapterConnection( _service, 0 )
	{

	}
	//////////////////////////////////////////////////////////////////////////
	class CreateSessionResponse
		: public Response
	{
	public:
		CreateSessionResponse( const ClientPtr & _client, const ConnectionCachePtr & _connectionCache )
			: m_client(_client)
			, m_connectionCache(_connectionCache)
		{
		}

	public:
		void responseCall( ArchiveRead & _ar ) override
		{
			Proxy_PlayerPtr player = makeProxy<Proxy_Player>( _ar, m_connectionCache );
			
			m_client->onConnect( player );
		}

	protected:
		ClientPtr m_client;
		ConnectionCachePtr m_connectionCache;
	};
	//////////////////////////////////////////////////////////////////////////
	void RouterConnection::createSession( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _login, const std::string & _password, const ClientPtr & _client )
	{
		this->connect( _endpoint );

		ArchiveWrite & ar = this->beginConnection();

		std::size_t dispatchId = this->addDispatch( new CreateSessionResponse( _client, m_connectionCache ) );

		ar.writeSize( dispatchId );

		ar.writeString( _login );
		ar.writeString( _password );

		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	ConnectionPtr RouterConnection::createConnection( std::size_t _endpointId )
	{
		RouterProxyConnectionPtr cn = new RouterProxyConnection( this, _endpointId );

		return cn;
	}
}