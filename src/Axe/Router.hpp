#	pragma once

#	include "Servant.hpp"
#	include "Response.hpp"

#	include "GridConnection.hpp"

#	include "AxeProtocols/Player.hpp"

namespace Axe
{
	typedef AxeHandle<class Connection> ConnectionPtr;
	typedef AxeHandle<class RouterSession> RouterSessionPtr;	

	class Router
		: public Service
		, public ConnectionProvider
	{
	public:
		Router( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name );

	public:
		void initialize( const boost::asio::ip::tcp::endpoint & _grid );

	public:
		void start( const Proxy_GridManagerPtr & _gridManager );

	public:
		void onPermissionsVerifier( const Proxy_PermissionsVerifierPtr & _permissionsVerifier );
		void onSessionManager( const Proxy_SessionManagerPtr & _sessionManager );

	public:
		void dispatchMethod( ArchiveRead & _ar, std::size_t _size, const RouterSessionPtr & _sn );
		void permissionVerify( const std::string & _login, const std::string & _password, const SessionPtr & _session );

	public:
		ConnectionPtr createConnection( std::size_t _hostId ) override;

	protected:
		SessionPtr makeSession() override;

	protected:
		Proxy_SessionManagerPtr m_sessionManager;
		Proxy_PermissionsVerifierPtr m_permissionsVerifier;

		Proxy_GridManagerPtr m_gridManager;

		ConnectionCachePtr m_connectionCache;
		EndpointCachePtr m_endpointCache;
	};

	typedef AxeHandle<Router> RouterPtr;
}