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
		void start( const Proxy_PermissionsVerifierPtr & _permissionsVerifier, const Proxy_SessionManagerPtr & _sessionManager );

	public:
		void dispatchMethod( std::size_t _sizeArgs, std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, std::size_t _endpointId, const RouterSessionPtr & _sn );
		void permissionVerify( const std::string & _login, const std::string & _password, const SessionPtr & _session );

	public:
		ConnectionPtr createConnection( std::size_t _endpointId ) override;

	protected:
		SessionPtr makeSession() override;

	protected:
		ConnectionCachePtr m_connectionCache;

		Proxy_SessionManagerPtr m_sessionManager;
		Proxy_PermissionsVerifierPtr m_permissionsVerifier;
	};

	typedef AxeHandle<Router> RouterPtr;
}