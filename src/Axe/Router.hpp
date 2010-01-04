#	pragma once

#	include <Axe/Service.hpp>

#	include <AxeProtocols/SessionManager.hpp>
#	include <AxeProtocols/PermissionsVerifier.hpp>

namespace Axe
{
	typedef AxeHandle<class Communicator> CommunicatorPtr;	
	typedef AxeHandle<class RouterSession> RouterSessionPtr;	

	class Router
		: public Service
	{
	public:
		Router( const CommunicatorPtr & _communicator, const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name );

	public:
		void start();

	public:
		void onPermissionsVerifier( const Proxy_PermissionsVerifierPtr & _permissionsVerifier );
		void onSessionManager( const Proxy_SessionManagerPtr & _sessionManager );

	public:
		void dispatchMethod( ArchiveDispatcher & _ar, std::size_t _size, const RouterSessionPtr & _sn );
		void permissionVerify( const std::string & _login, const std::string & _password, const SessionPtr & _session );

	protected:
		SessionPtr makeSession() override;

	protected:
		void getPermissionsVerifierResponse( const ProxyPtr & _unique );
		void getSessionManagerResponse( const ProxyPtr & _unique );

		void checkPermissionsResponse( bool _successful, const std::string & _login, const SessionPtr & _session );
		void createResponse( const Proxy_SessionPtr & _player, const SessionPtr & _session );

	protected:
		CommunicatorPtr m_communicator;

		Proxy_SessionManagerPtr m_sessionManager;
		Proxy_PermissionsVerifierPtr m_permissionsVerifier;
	};

	typedef AxeHandle<Router> RouterPtr;
}