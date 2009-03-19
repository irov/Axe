#	pragma once

#	include <Axe/Shared.hpp>
#	include <Axe/ArchiveWrite.hpp>
#	include <Axe/ArchiveRead.hpp>

namespace Axe
{
	class Dispatcher
		: virtual public Shared
	{
	public:
		Dispatcher( boost::asio::io_service & _service, const ConnectionCachePtr & _connectionCache );

	public:
		void process();

	public:
		boost::asio::ip::tcp::socket & getSocket();

		ArchiveRead & getArchiveRead();
		ArchiveWrite & getArchiveWrite();

	protected:
		void processArchive( const Archive & _ar );

	public:
		void run();
		void close();

	protected:
		void handleWriteStream( const boost::system::error_code & _ec );

	protected:
		void handleReadBodySize( const boost::system::error_code & _ec, std::size_t * _size );
		void handleReadBody( const boost::system::error_code & _ec );

	public:
		virtual void dispatchMessage( ArchiveRead & _ar, std::size_t _size ) = 0;

	protected:
		static bool handleReadCondition( const boost::system::error_code & _ec, std::size_t _read, std::size_t _wait );

	protected:
		ArchiveWrite m_streamWrite;
		ArchiveWrite m_streamSend;

		ArchiveRead m_streamIn;

		ConnectionCachePtr m_connectionCache;

		boost::asio::ip::tcp::socket m_socket;
	};
}