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
		
	}
	//////////////////////////////////////////////////////////////////////////
	class RouterResponse_GridManager_getUniqueSessionManager
		: public Response_GridManager_getUnique
	{
	public:
		RouterResponse_GridManager_getUniqueSessionManager( const RouterPtr & _router, const Proxy_PermissionsVerifierPtr & _permissionsVerifier )
			: m_router(_router)
			, m_permissionsVerifier(_permissionsVerifier)
		{
		}

	protected:
		void response( const Proxy_UniquePtr & _unique ) override
		{
			Proxy_SessionManagerPtr sessionManager = uncheckedCast<Proxy_SessionManagerPtr>( _unique );

			m_router->start( m_permissionsVerifier, sessionManager );
		}

	protected:
		RouterPtr m_router;
		Proxy_PermissionsVerifierPtr m_permissionsVerifier;
	};
	//////////////////////////////////////////////////////////////////////////
	class RouterResponse_GridManager_getUniquePermissionsVerifier
		: public Response_GridManager_getUnique
	{
	public:
		RouterResponse_GridManager_getUniquePermissionsVerifier( const RouterPtr & _router, const Proxy_GridManagerPtr & _gridManager )
			: m_router(_router)
			, m_gridManager(_gridManager)
		{

		}

	protected:
		void response( const Proxy_UniquePtr & _unique ) override
		{
			m_permissionsVerifier = uncheckedCast<Proxy_PermissionsVerifierPtr>( _unique );

			m_gridManager->getUnique( "SessionManager"
				, new RouterResponse_GridManager_getUniqueSessionManager( m_router, m_permissionsVerifier ) 
				);
		}

	protected:
		RouterPtr m_router;
		Proxy_GridManagerPtr m_gridManager;
		Proxy_PermissionsVerifierPtr m_permissionsVerifier;
	};
	//////////////////////////////////////////////////////////////////////////
	class RouterGridConnectResponse
		: public GridConnectResponse
	{
	public:
		RouterGridConnectResponse( const RouterPtr & _router )
			: m_router(_router)
		{
		}

	protected:
		void connectSuccessful( const Proxy_GridManagerPtr & _gridManager )
		{
			m_gridManager = _gridManager;

			m_gridManager->getUnique( "PermissionsVerifier"
				, new RouterResponse_GridManager_getUniquePermissionsVerifier( m_router, m_gridManager ) 
				);
		}

		void connectFailed()
		{

		}

	protected:
		RouterPtr m_router;

		Proxy_GridManagerPtr m_gridManager;
	};	
	//////////////////////////////////////////////////////////////////////////
	void Router::initialize( const boost::asio::ip::tcp::endpoint & _grid )
	{
		GridConnectionPtr gridConnection = new GridConnection( m_service, m_connectionCache
			, new RouterGridConnectResponse( this ) 
			);

		gridConnection->connect( _grid );
	}
	//////////////////////////////////////////////////////////////////////////
	void Router::start( const Proxy_PermissionsVerifierPtr & _permissionsVerifier, const Proxy_SessionManagerPtr & _sessionManager )
	{
		m_sessionManager = _sessionManager;
		m_permissionsVerifier = _permissionsVerifier;

		this->accept();
	}
	//////////////////////////////////////////////////////////////////////////
	void Router::dispatchMethod( std::size_t _sizeArgs, std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, std::size_t _hostId, const RouterSessionPtr & _session )
	{
		const ConnectionPtr & cn = m_connectionCache->getConnection( _hostId );

		ArchiveWrite & write = cn->beginMessage( _servantId, _methodId, new RouterResponse( _requestId, _session ) );

		ArchiveRead & read = _session->getArchiveRead();

		const Archive::value_type * args_buff = read.selectBuffer( _sizeArgs );

		write.writeArchive( args_buff, _sizeArgs );

		cn->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	class RouterResponse_SessionManager_create
		: public Response_SessionManager_create
	{
	public:
		RouterResponse_SessionManager_create( const SessionPtr & _session )
			: m_session(_session)
		{
		}

	protected:
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
	class RouterResponse_PermissionsVerifier_checkPermissions
		: public Response_PermissionsVerifier_checkPermissions
	{
	public:
		RouterResponse_PermissionsVerifier_checkPermissions( const std::string & _login, const Proxy_SessionManagerPtr & _sessionManager, const SessionPtr & _session )
			: m_login(_login)
			, m_session(_session)
			, m_sessionManager(_sessionManager)			
		{
		}

	public:
		void response( bool _successful ) override
		{
			m_sessionManager->create( m_login
				, new RouterResponse_SessionManager_create( m_session ) 
				);
		}

	protected:
		std::string m_login;

		SessionPtr m_session;
		Proxy_SessionManagerPtr m_sessionManager;
	};
	//////////////////////////////////////////////////////////////////////////
	void Router::permissionVerify( const std::string & _login, const std::string & _password, const SessionPtr & _session )
	{
		m_permissionsVerifier->checkPermissions( _login, _password
			, new RouterResponse_PermissionsVerifier_checkPermissions( _login, m_sessionManager, _session ) 
			);
	}
	//////////////////////////////////////////////////////////////////////////
	ConnectionPtr Router::createConnection( std::size_t _hostId )
	{
		AdapterConnectionPtr cn = new AdapterConnection( m_service, m_connectionCache, _hostId );

		return cn;
	}
	//////////////////////////////////////////////////////////////////////////
	SessionPtr Router::makeSession()
	{
		RouterSessionPtr session = new RouterSession( m_service, this );

		return session;
	}
}
