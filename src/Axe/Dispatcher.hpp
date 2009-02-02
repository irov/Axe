#	pragma once

#	include "Shared.hpp"
#	include "Archive.hpp"

namespace Axe
{
	class ArchiveWrite;
	class ArchiveRead;

	class Dispatcher
		: virtual public Shared
	{
	public:
		Dispatcher( boost::asio::io_service & _service );

	public:
		void process();

	public:
		boost::asio::ip::tcp::socket & getSocket();

		ArchiveRead & getArchiveRead();
		ArchiveWrite & getArchiveWrite();

	protected:
		void run();
		void close();

	protected:
		void handleWriteStream( const boost::system::error_code & _ec );

	protected:
		void handleReadBodySize( const boost::system::error_code & _ec, std::size_t * _size );
		void handleReadBody( const boost::system::error_code & _ec, Archive::value_type * _blob );

	public:
		virtual void dispatchMessage( ArchiveRead & _ar, std::size_t _size ) = 0;

	protected:
		static bool handleReadCondition( const boost::system::error_code & _ec, std::size_t _read, std::size_t _wait );

	protected:
		ArchiveWrite m_streamWrite;
		ArchiveWrite m_streamSend;

		ArchiveRead m_streamIn;

		boost::asio::ip::tcp::socket m_socket;
	};
}