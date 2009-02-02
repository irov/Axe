#	pragma once

#	include "Host.hpp"
#	include "Response.hpp"

#	include "AxeProtocols/Player.hpp"

namespace Axe
{
	typedef AxeHandle<class Connection> ConnectionPtr;
	typedef AxeHandle<class RouterSession> RouterSessionPtr;	

	class Router
		: public Host
	{
	public:
		Router( const boost::asio::ip::tcp::endpoint & _endpoint );

	public:
		void initialize();

	public:
		void dispatchMethod( std::size_t _sizeArgs, std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, std::size_t _endpointId, const RouterSessionPtr & _sn );
		void permissionVerify( ArchiveRead & _ar, std::size_t _size, const SessionPtr & _session );

	protected:
		SessionPtr makeSession() override;

	protected:
		typedef std::map<std::size_t, ConnectionPtr> TMapRouming;
		TMapRouming m_rouming;

		Proxy_SessionManagerPtr m_sessionManager;
	};

	typedef AxeHandle<Router> RouterPtr;
}