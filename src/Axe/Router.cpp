#	include "pch.hpp"

#	include "Router.hpp"
#	include "RouterResponse.hpp"
#	include "RouterSession.hpp"

#	include "Connection.hpp"
#	include "ArchiveWrite.hpp"
#	include "ArchiveRead.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Router::Router( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name )
		: Service(_endpoint, _name)
	{
		m_connectionCache = new ConnectionCache( this );
		m_gridConnection = new GridConnection( m_service, m_connectionCache, this );
	}
	//////////////////////////////////////////////////////////////////////////
	void Router::initialize( const boost::asio::ip::tcp::endpoint & _grid )
	{
		m_gridConnection->connect( _grid );
	}
	//////////////////////////////////////////////////////////////////////////
	void Router::dispatchMethod( std::size_t _sizeArgs, std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, std::size_t _endpointId, const RouterSessionPtr & _session )
	{
		const ConnectionPtr & cn = m_connectionCache->getConnection( _endpointId );

		ArchiveWrite & write = cn->beginMessage( _servantId, _methodId, new RouterResponse( _requestId, _session ) );

		ArchiveRead & read = _session->getArchiveRead();

		const Archive::value_type * args_buff = read.selectBuffer( _sizeArgs );

		write.writeArchive( args_buff, _sizeArgs );

		cn->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	class RouterResponse_SessionManager_login
		: public Response_SessionManager_login
	{
	public:
		RouterResponse_SessionManager_login( const SessionPtr & _session )
			: m_session(_session)
		{
		}

	public:
		void response( const Proxy_PlayerPtr & _player ) override
		{
			ArchiveWrite & ar = m_session->beginConnect( true );
			ar << _player;
			m_session->process();
		}

	protected:
		SessionPtr m_session;
	};
	//////////////////////////////////////////////////////////////////////////
	void Router::permissionVerify( const std::string & _login, const std::string & _password, const SessionPtr & _session )
	{
		m_sessionManager->login( _login, _password, new RouterResponse_SessionManager_login( _session ) );
	}
	//////////////////////////////////////////////////////////////////////////
	ConnectionPtr Router::createConnection( std::size_t _endpointId ) override
	{
		AdapterConnectionPtr cn = new AdapterConnection( m_service, m_connectionCache, _endpointId );

		return cn;
	}
	//////////////////////////////////////////////////////////////////////////
	SessionPtr Router::makeSession()
	{
		RouterSessionPtr session = new RouterSession( m_service, this );

		return session;
	}
	//////////////////////////////////////////////////////////////////////////
	void Router::connectSuccessful( const Proxy_GridManagerPtr & _gridManager )
	{
		m_gridManager = _gridManager;

		this->accept();
	}
	//////////////////////////////////////////////////////////////////////////
	void Router::connectFailed()
	{

	}
}
