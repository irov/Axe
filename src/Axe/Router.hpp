#	pragma once

#	include "Servant.hpp"
#	include "Response.hpp"

#	include "GridConnection.hpp"

#	include "AxeProtocols/Player.hpp"

namespace Axe
{
	typedef AxeHandle<class Connection> ConnectionPtr;
	typedef AxeHandle<class Communicator> CommunicatorPtr;	
	typedef AxeHandle<class RouterSession> RouterSessionPtr;	

	class Router
		: public Service
	{
	public:
		Router( const CommunicatorPtr & _communicator, const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name );

	public:
		void run();

	public:
		void onPermissionsVerifier( const Proxy_PermissionsVerifierPtr & _permissionsVerifier );
		void onSessionManager( const Proxy_SessionManagerPtr & _sessionManager );

	public:
		void dispatchMethod( ArchiveRead & _ar, std::size_t _size, const RouterSessionPtr & _sn );
		void permissionVerify( const std::string & _login, const std::string & _password, const SessionPtr & _session );

	protected:
		SessionPtr makeSession() override;

	protected:
		ConnectionCachePtr m_connectionCache;
		EndpointCachePtr m_endpointCache;

		Proxy_GridManagerPtr m_gridManager;

		Proxy_SessionManagerPtr m_sessionManager;
		Proxy_PermissionsVerifierPtr m_permissionsVerifier;
	};

	typedef AxeHandle<Router> RouterPtr;
}