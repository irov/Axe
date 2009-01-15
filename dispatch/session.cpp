#	include "pch.hpp"

#	include "session.hpp"

#	include "stream.hpp"

static bool handle_read_condition( const boost::system::error_code & _ec, std::size_t _read, std::size_t _wait )
{
	return ( _read >= _wait );
}

session::session( boost::asio::io_service & _service )
: m_socket(_service)
{
	m_streamWrite = new stream_write();
	m_streamSend = new stream_write();
	m_streamIn = new stream_read();
}

boost::asio::ip::tcp::socket & session::get_socket()
{
	return m_socket;
}

stream_read * session::get_streamIn()
{
	return m_streamIn;
}

stream_write * session::get_streamOut()
{
	return m_streamWrite;
}

void session::accept()
{
	this->run();
}

void session::connect( const boost::asio::ip::tcp::endpoint & _endpoint )
{
	m_socket.async_connect( _endpoint
		, boost::bind( &session::handle_connect, this, boost::asio::placeholders::error ) 
		);
}

void session::handle_connect( const boost::system::error_code & _ec )
{
	this->run();
}

void session::run()
{
	std::size_t * size;
	m_streamIn->keep_value( &size );

	boost::asio::async_read( m_socket
		, boost::asio::buffer( size, sizeof(std::size_t) )
		, boost::bind( &handle_read_condition, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, sizeof(std::size_t) )
		, boost::bind( &session::handle_read_size, this, boost::asio::placeholders::error, size )
		);
}


void session::procces()
{
	if( m_streamSend->empty() )
	{
		std::swap( m_streamWrite, m_streamSend );

		const TBlobject & blob = m_streamSend->getBuffer();

		boost::asio::async_write( m_socket
			, boost::asio::buffer( blob )
			, boost::bind( &session::handle_write_stream, this, boost::asio::placeholders::error )
			);
	}
}

void session::handle_write_stream( const boost::system::error_code & _ec )
{
	m_streamSend->clear();

	if( m_streamWrite->empty() == false )
	{
		this->procces();
	}
}

void session::handle_read_size( const boost::system::error_code & _ec, std::size_t * _size )
{
	std::size_t size_blob = *_size - sizeof(std::size_t);
	TBlobject::value_type * blob = m_streamIn->keep( size_blob );

	boost::asio::async_read( m_socket
		, boost::asio::buffer( blob, size_blob )
		, boost::bind( &handle_read_condition, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, size_blob )
		, boost::bind( &session::handle_read_blob, this, boost::asio::placeholders::error, blob )
		);
}

void session::handle_read_blob( const boost::system::error_code & _ec, TBlobject::value_type * _blob )
{
	if( !_ec )
	{
		m_streamIn->begin();

		std::size_t size;
		m_streamIn->read( size );

		this->dispatch_message( size );
		run();
	}
}