#	pragma once

#	include <AxeUtil/Shared.hpp>
#	include <AxeUtil/Archive.hpp>

#	include <Axe/ArchiveInvocation.hpp>
#	include <Axe/ArchiveDispatcher.hpp>

namespace Axe
{
	class ArchiveInvocation;
	class ArchiveDispatcher;

	typedef AxeHandle<class Response> ResponsePtr;
	typedef AxeHandle<class ConnectionCache> ConnectionCachePtr;

	class Connection
		: virtual public AxeUtil::Shared
	{
	public:
		Connection( const SocketPtr & _socket, const ConnectionCachePtr & _connectionCache );

	public:
		ArchiveInvocation & connect( const boost::asio::ip::tcp::endpoint & _endpoint );
		void close();

	protected:
		void handleConnect( const boost::system::error_code & _ec );

		void handleReadConnectSize( const boost::system::error_code & _ec, std::size_t * _size );
		void handleReadConnect( const boost::system::error_code & _ec, AxeUtil::Archive::value_type * _blob );

	public:
		virtual ArchiveInvocation & beginMessage( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response ) = 0;
		virtual void processMessage() = 0;

	protected:
		virtual void connectionSuccessful( ArchiveDispatcher & _ar, std::size_t _size ) = 0;
		virtual void connectionFailed( ArchiveDispatcher & _ar, std::size_t _size ) = 0;

	protected:
		virtual void reconnect() = 0;

	protected:
		ArchiveInvocation m_permission;
		ArchiveDispatcher m_streamIn;

		SocketPtr m_socket;
	};

	typedef AxeHandle<Connection> ConnectionPtr;
}