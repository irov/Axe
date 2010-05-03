#	pragma once

#	include <AxeUtil/Shared.hpp>
#	include <AxeUtil/Archive.hpp>

#	include <Axe/Socket.hpp>

#	include <Axe/ArchiveInvocation.hpp>
#	include <Axe/ArchiveDispatcher.hpp>

namespace Axe
{
	typedef AxeHandle<class Response> ResponsePtr;
	typedef AxeHandle<class ConnectionCache> ConnectionCachePtr;

	enum EConnectionStatus
	{
		ECS_ERROR,
		ECS_SUCCESSFUL,
		ECS_FAILED,
		ECS_LAST
	};

	typedef boost::function3<void, EConnectionStatus, ArchiveDispatcher &, std::size_t> FConnectionConnect;

	class Connection
		: virtual public AxeUtil::Shared
	{
	public:
		Connection( const SocketPtr & _socket, const ConnectionCachePtr & _connectionCache );

	public:
		const SocketPtr & getSocket() const;
		const ConnectionCachePtr & getConnectionCache() const;

		ArchiveInvocation & getArchiveInvocation();
	
	public:
		ArchiveInvocation & connect( const boost::asio::ip::tcp::endpoint & _endpoint, FConnectionConnect _response );
		void close();

	protected:
		void handleConnect( const boost::system::error_code & _ec, FConnectionConnect _response );

		void handleReadConnectSize( const boost::system::error_code & _ec, std::size_t * _size, FConnectionConnect _response );
		void handleReadConnect( const boost::system::error_code & _ec, AxeUtil::Archive::value_type * _blob, FConnectionConnect _response );

	public:
		void process();
		void run();

	public:
		virtual void write( ArchiveInvocation & _ar ) const = 0;

	protected:
		void handleReadBodySize( const boost::system::error_code & _ec, std::size_t * _size );
		void handleReadBody( const boost::system::error_code & _ec );

	public:
		virtual ArchiveInvocation & beginMessage( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response ) = 0;
		virtual void dispatchMessage( ArchiveDispatcher & _ar, std::size_t _size ) = 0;

	protected:
		virtual void _reconnect();

	protected:		
		void processArchive( const AxeUtil::Archive & _ar );
		void handleWriteStream( const boost::system::error_code & _ec );

	protected:
		SocketPtr m_socket;
		ConnectionCachePtr m_connectionCache;

		ArchiveInvocation m_permission;

		ArchiveDispatcher m_streamIn;
		ArchiveInvocation m_streamOut;

	private:
		AxeUtil::Archive m_archiveSend;
	};

	typedef AxeHandle<Connection> ConnectionPtr;
}