#	include "pch.hpp"

#	include <Axe/Router.hpp>

#	include <Axe/Communicator.hpp>

#	include <Axe/RouterResponse.hpp>
#	include <Axe/RouterSession.hpp>

#	include <Axe/Connection.hpp>
#	include <Axe/ArchiveWrite.hpp>
#	include <Axe/ArchiveRead.hpp>

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
	void Router::getSessionManagerResponse( const Proxy_UniquePtr & _unique )
	{
		m_sessionManager = uncheckedCast<Proxy_SessionManagerPtr>( _unique );

		Service::accept();
	}
	//////////////////////////////////////////////////////////////////////////
	void Router::getPermissionsVerifierResponse( const Proxy_UniquePtr & _unique )
	{
		m_permissionsVerifier = uncheckedCast<Proxy_PermissionsVerifierPtr>( _unique );

		m_gridManager->getUnique_async( 
			bindResponse( boost::bind( &Router::getSessionManagerResponse, handlePtr(this), _1 ) )
			, "SessionManager"
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Router::run()
	{
		m_gridManager->getUnique_async(
			bindResponse( boost::bind( &Router::getPermissionsVerifierResponse, handlePtr(this), _1 ) )
			, "PermissionsVerifier"
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
	void Router::createResponse( const Proxy_PlayerPtr & _player, const SessionPtr & _session )
	{
		ArchiveWrite & ar = _session->beginConnect( true );
		ar << _player;
		_session->process();
		_session->run();
	}
	//////////////////////////////////////////////////////////////////////////
	void Router::checkPermissionsResponse( bool _successful, const std::string & _login, const SessionPtr & _session )
	{
		if( _session )
		{
			m_sessionManager->create_async( 
				bindResponse( boost::bind( &Router::createResponse, handlePtr(this), _1, _session ) )
				, _login
				);
		}
		else
		{
			_session->close();
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void Router::permissionVerify( const std::string & _login, const std::string & _password, const SessionPtr & _session )
	{
		m_permissionsVerifier->checkPermissions_async( 
			bindResponse( boost::bind( &Router::checkPermissionsResponse, handlePtr(this), _1, _login, _session ) )
			, _login
			, _password
			);
	}
	//////////////////////////////////////////////////////////////////////////
	SessionPtr Router::makeSession()
	{
		RouterSessionPtr session = new RouterSession( m_service, this, m_connectionCache );

		return session;
	}
}
