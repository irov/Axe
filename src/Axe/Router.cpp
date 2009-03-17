#	include "pch.hpp"

#	include "Router.hpp"

#	include "Communicator.hpp"

#	include "RouterResponse.hpp"
#	include "RouterSession.hpp"

#	include "Connection.hpp"
#	include "ArchiveWrite.hpp"
#	include "ArchiveRead.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Router::Router(  const CommunicatorPtr & _communicator, const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name )
		: Service(_communicator->getService(), _endpoint, _name)
		, m_connectionCache(_communicator->getConnectionCache())
		, m_endpointCache(_communicator->getEndpointCache())
		, m_gridManager(_communicator->getGridManager())

	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Router::onSessionManager( const Proxy_SessionManagerPtr & _sessionManager )
	{
		m_sessionManager = _sessionManager;

		Service::accept();
	}
	//////////////////////////////////////////////////////////////////////////
	class RouterResponse_GridManager_getUniqueSessionManager
		: public Response_GridManager_getUnique
	{
	public:
		RouterResponse_GridManager_getUniqueSessionManager( const RouterPtr & _router )
			: m_router(_router)
		{
		}

	protected:
		void response( const Proxy_UniquePtr & _unique ) override
		{
			Proxy_SessionManagerPtr sessionManager = uncheckedCast<Proxy_SessionManagerPtr>( _unique );

			m_router->onSessionManager( sessionManager );
		}

		void throw_exception( const Axe::Exception & _ex ) override
		{
		}

	protected:
		RouterPtr m_router;
		
	};
	//////////////////////////////////////////////////////////////////////////
	void Router::onPermissionsVerifier( const Proxy_PermissionsVerifierPtr & _permissionsVerifier )
	{
		m_permissionsVerifier = _permissionsVerifier;

		m_gridManager->getUnique( "SessionManager"
			, new RouterResponse_GridManager_getUniqueSessionManager( this ) 
			);
	}
	//////////////////////////////////////////////////////////////////////////
	class RouterResponse_GridManager_getUniquePermissionsVerifier
		: public Response_GridManager_getUnique
	{
	public:
		RouterResponse_GridManager_getUniquePermissionsVerifier( const RouterPtr & _router )
			: m_router(_router)
		{
		}

	protected:
		void response( const Proxy_UniquePtr & _unique ) override
		{
			Proxy_PermissionsVerifierPtr permissionsVerifier = uncheckedCast<Proxy_PermissionsVerifierPtr>( _unique );

			m_router->onPermissionsVerifier( permissionsVerifier );
		}

		void throw_exception( const Axe::Exception & _ex ) override
		{

		}

	protected:
		RouterPtr m_router;
	};
	//////////////////////////////////////////////////////////////////////////
	void Router::run()
	{
		m_gridManager->getUnique( "PermissionsVerifier"
			, new RouterResponse_GridManager_getUniquePermissionsVerifier( this ) 
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Router::dispatchMethod( ArchiveRead & _ar, std::size_t _size, const RouterSessionPtr & _session )
	{
		std::size_t servantId;
		std::size_t methodId;
		std::size_t requestId;
		std::size_t hostId;

		_ar.read( servantId);
		_ar.readSize( methodId);
		_ar.readSize( requestId);
		_ar.readSize( hostId );

		const ConnectionPtr & cn = m_connectionCache->getConnection( hostId );

		ArchiveWrite & write = cn->beginMessage( servantId, methodId, new RouterResponse( requestId, _session ) );

		std::size_t lenght = _ar.length( _size );

		const Archive::value_type * args_buff = _ar.selectBuffer( lenght );

		write.writeArchive( args_buff, lenght );

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
			m_session->run();
		}

		void throw_exception( const Axe::Exception & _ex ) override
		{

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

		void throw_exception( const Axe::Exception & _ex ) override
		{

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
	SessionPtr Router::makeSession()
	{
		RouterSessionPtr session = new RouterSession( m_service, this, m_connectionCache );

		return session;
	}
}
