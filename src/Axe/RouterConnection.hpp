#	pragma once

#	include <Axe/Connection.hpp>
#	include <Axe/Dispatcher.hpp>

#	include <Axe/ConnectionCache.hpp>
#	include <Axe/ClientConnectResponse.hpp>

namespace Axe
{
	typedef AxeHandle<class Proxy_Session> Proxy_SessionPtr;

	class RouterConnectionResponse
		: virtual public AxeUtil::Shared
	{
	public:
		virtual void response( const Proxy_SessionPtr & _session ) = 0;
		virtual void throw_exception( const Exception & _ex ) = 0;
	};

	typedef AxeHandle<RouterConnectionResponse> RouterConnectionResponsePtr;

	class RouterConnection
		: public Connection
		, public Dispatcher
	{
	public:
		RouterConnection( const SocketPtr & _socket, const ConnectionCachePtr & _connectionCache );

	public:
		void createSession( const boost::asio::ip::tcp::endpoint & _endpoint
			, const std::string & _login
			, const std::string & _password
			, const RouterConnectionResponsePtr & _cb
			);

	public:
		ConnectionPtr createProxyConnection( std::size_t _adapterId );

	protected:
		void write( ArchiveInvocation & _ar ) const override;

	protected:
		ConnectionCachePtr m_connectionCache;
	};

	typedef AxeHandle<RouterConnection> RouterConnectionPtr;
}