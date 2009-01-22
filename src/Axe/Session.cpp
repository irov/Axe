#	include "pch.hpp"

#	include "Session.hpp"

#	include "ArchiveWrite.hpp"
#	include "ArchiveRead.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	static bool handle_read_condition( const boost::system::error_code & _ec, std::size_t _read, std::size_t _wait )
	{
		return ( _read >= _wait );
	}
	//////////////////////////////////////////////////////////////////////////
	Session::Session( boost::asio::io_service & _service )
		: m_socket(_service)
	{
		m_streamWrite = new ArchiveWrite();
		m_streamSend = new ArchiveWrite();
		m_streamIn = new ArchiveRead();
	}
	//////////////////////////////////////////////////////////////////////////
	boost::asio::ip::tcp::socket & Session::getSocket()
	{
		return m_socket;
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveRead & Session::getArchiveRead()
	{
		return *m_streamIn;
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveWrite & Session::getArchiveWrite()
	{
		return *m_streamWrite;
	}
	//////////////////////////////////////////////////////////////////////////
	void Session::accept()
	{
		this->run();
	}
	//////////////////////////////////////////////////////////////////////////
	void Session::connect( const boost::asio::ip::tcp::endpoint & _endpoint )
	{
		m_socket.async_connect( _endpoint
			, boost::bind( &Session::handleConnect, this, boost::asio::placeholders::error ) 
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Session::handleConnect( const boost::system::error_code & _ec )
	{
		this->run();
	}
	//////////////////////////////////////////////////////////////////////////
	void Session::run()
	{
		std::size_t * size = m_streamIn->keep<std::size_t>();

		boost::asio::async_read( m_socket
			, boost::asio::buffer( size, sizeof(std::size_t) )
			, boost::bind( &handle_read_condition, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, sizeof(std::size_t) )
			, boost::bind( &Session::handleReadSize, this, boost::asio::placeholders::error, size )
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Session::process()
	{
		if( m_streamSend->empty() )
		{
			std::swap( m_streamWrite, m_streamSend );

			const Archive & blob = m_streamSend->getArchive();

			boost::asio::async_write( m_socket
				, boost::asio::buffer( blob )
				, boost::bind( &Session::handleWriteStream, this, boost::asio::placeholders::error )
				);
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void Session::handleWriteStream( const boost::system::error_code & _ec )
	{
		m_streamSend->clear();

		if( m_streamWrite->empty() == false )
		{
			this->process();
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void Session::handleReadSize( const boost::system::error_code & _ec, std::size_t * _size )
	{
		std::size_t size_blob = *_size - sizeof(std::size_t);

		Archive::value_type * blob = m_streamIn->keepBuffer( size_blob );

		boost::asio::async_read( m_socket
			, boost::asio::buffer( blob, size_blob )
			, boost::bind( &handle_read_condition, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, size_blob )
			, boost::bind( &Session::handleReadBody, this, boost::asio::placeholders::error, blob )
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Session::handleReadBody( const boost::system::error_code & _ec, Archive::value_type * _blob )
	{
		if( !_ec )
		{
			m_streamIn->begin();

			std::size_t size;
			m_streamIn->read( size );

			this->dispatchMessage( size );
			this->run();
		}
	}
}