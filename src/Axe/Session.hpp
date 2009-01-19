#	pragma once

#	include "blobject_stream.hpp"

namespace Axe
{
	class ArchiveWrite;
	class ArchiveRead;

	class Session
		: public Shared
	{
	public:
		Session( boost::asio::io_service & _service );

	public:
		void accept();
		void connect( const boost::asio::ip::tcp::endpoint & _endpoint );
		void procces();

	public:
		boost::asio::ip::tcp::socket & getSocket();

		ArchiveRead & getArchiveRead();
		ArchiveWrite & getArchiveWrite();

	protected:
		void handleConnect( const boost::system::error_code & _ec );

	protected:
		void handleWriteStream( const boost::system::error_code & _ec );

	protected:
		void handleReadSize( const boost::system::error_code & _ec, std::size_t * _size );
		void handleReadBody( const boost::system::error_code & _ec, TBlobject::value_type * _blob );

	protected:
		void run();

	public:
		virtual void dispatchMessage( std::size_t _size ) = 0;

	protected:
		ArchiveWrite * m_streamWrite;
		ArchiveWrite * m_streamSend;

		ArchiveRead * m_streamIn;

		boost::asio::ip::tcp::socket m_socket;
	};
}