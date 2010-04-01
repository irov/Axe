#	include "pch.hpp"

#	include <Axe/Router.hpp>

#	include <Axe/Communicator.hpp>

#	include <Axe/RouterResponse.hpp>
#	include <Axe/RouterSession.hpp>

#	include <Axe/Connection.hpp>
#	include <Axe/ConnectionCache.hpp>

#	include <Axe/ArchiveInvocation.hpp>
#	include <Axe/ArchiveDispatcher.hpp>

#	include <AxeProtocols/GridManager.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Router::Router(  const CommunicatorPtr & _communicator, const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name )
		: Service(_communicator->getService(), _endpoint, _name)
		, m_communicator(_communicator)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Router::getSessionManagerResponse( const ProxyPtr & _unique )
	{
		m_sessionManager = uncheckedCast<Proxy_SessionManagerPtr>( _unique );

		Service::accept();
	}
	//////////////////////////////////////////////////////////////////////////
	void Router::getPermissionsVerifierResponse( const ProxyPtr & _unique )
	{
		m_permissionsVerifier = uncheckedCast<Proxy_PermissionsVerifierPtr>( _unique );

		const Proxy_GridManagerPtr & gridManager = m_communicator->getGridManager();

		gridManager->getUnique_async( 
			bindResponse( boost::bind( &Router::getSessionManagerResponse, handlePtr(this), _1 )
				, noneExceptionFilter() )
			, "SessionManager"
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Router::start()
	{
		const Proxy_GridManagerPtr & gridManager = m_communicator->getGridManager();

		gridManager->getUnique_async(
			bindResponse( boost::bind( &Router::getPermissionsVerifierResponse, handlePtr(this), _1 )
				, noneExceptionFilter() )
			, "PermissionsVerifier"
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Router::dispatchMethod( ArchiveDispatcher & _ar, std::size_t _size, const RouterSessionPtr & _session )
	{
		std::size_t servantId;
		std::size_t methodId;
		std::size_t requestId;
		std::size_t adapterId;

		_ar.read( servantId);
		_ar.readSize( methodId);
		_ar.readSize( requestId);
		_ar.readSize( adapterId );

		const ConnectionCachePtr & connectionCache 
			= m_communicator->getConnectionCache();

		const ConnectionPtr & cn = connectionCache->getConnection( adapterId );

		ResponsePtr response = new RouterResponse( requestId, _session );

		ArchiveInvocation & write = cn->beginMessage( servantId, methodId, response );

		std::size_t lenght = _ar.length( _size );

		const AxeUtil::Archive::value_type * args_buff = _ar.selectBuffer( lenght );

		write.writeArchive( args_buff, lenght );

		cn->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Router::createResponse( const Proxy_SessionPtr & _player, const SessionPtr & _session )
	{
		ArchiveInvocation & ar = _session->beginConnect( true );
		ar << _player;
		_session->process();
		_session->run();
	}
	//////////////////////////////////////////////////////////////////////////
	void Router::checkPermissionsResponse( bool _successful, const std::string & _login, const SessionPtr & _session )
	{
		if( _successful )
		{
			m_sessionManager->create_async( 
				bindResponse( boost::bind( &Router::createResponse, handlePtr(this), _1, _session )
					, noneExceptionFilter() )
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
			bindResponse( boost::bind( &Router::checkPermissionsResponse, handlePtr(this), _1, _login, _session )
				, noneExceptionFilter() )
			, _login
			, _password
			);
	}
	//////////////////////////////////////////////////////////////////////////
	SessionPtr Router::makeSession()
	{
		const ConnectionCachePtr & connectionCache = m_communicator->getConnectionCache();

		SocketPtr socket = m_communicator->createSocket();

		RouterSessionPtr session = new RouterSession( socket, connectionCache, this );

		return session;
	}
}
