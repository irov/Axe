#	pragma once

#	include <AxeUtil/Shared.hpp>
#	include <AxeUtil/Archive.hpp>

#	include <Axe/Socket.hpp>
#	include <Axe/Exception.hpp>

#	include <Axe/ArchiveInvocation.hpp>
#	include <Axe/ArchiveDispatcher.hpp>

namespace Axe
{
	typedef AxeHandle<class Response> ResponsePtr;
	typedef AxeHandle<class ConnectionCache> ConnectionCachePtr;

	class ConnectionResponse
		: virtual public AxeUtil::Shared
	{
	public:
		virtual void response( ArchiveDispatcher & _ad, std::size_t _size ) = 0;
		virtual void throw_exception( const Exception & _ex ) = 0;
	};

	typedef AxeHandle<ConnectionResponse> ConnectionResponsePtr;

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
		ArchiveInvocation & connect( const boost::asio::ip::tcp::endpoint & _endpoint
			, const ConnectionResponsePtr & _cb
			);

		void close();

	protected:
		void handleConnect( const boost::system::error_code & _ec
			, const ConnectionResponsePtr & _cb
			);

		void handleReadConnectSize( const boost::system::error_code & _ec, std::size_t * _size
			, const ConnectionResponsePtr & _cb
			);

		void handleReadConnect( const boost::system::error_code & _ec, AxeUtil::Archive::value_type * _blob
			, const ConnectionResponsePtr & _cb
			);

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