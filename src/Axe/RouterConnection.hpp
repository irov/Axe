#	pragma once

#	include <Axe/Connection.hpp>
#	include <Axe/Dispatcher.hpp>

#	include <Axe/ConnectionCache.hpp>
#	include <Axe/ClientConnectResponse.hpp>

namespace Axe
{
	class RouterConnection
		: public Connection
		, public Dispatcher
	{
	public:
		RouterConnection( const SocketPtr & _socket, const ConnectionCachePtr & _connectionCache );

	public:
		void createSession( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _login, const std::string & _password );

	public:
		ConnectionPtr createProxyConnection( std::size_t _adapterId );

	protected:
		void connectionSuccessful( ArchiveDispatcher & _ar, std::size_t _size ) override;
		void connectionFailed( ArchiveDispatcher & _ar, std::size_t _size ) override;

	protected:
		void write( ArchiveInvocation & _ar ) const override;

	protected:
		ConnectionCachePtr m_connectionCache;
	};

	typedef AxeHandle<RouterConnection> RouterConnectionPtr;
}