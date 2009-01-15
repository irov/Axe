#	pragma once

#	include "blobject_stream.hpp"

class stream_write;
class stream_read;

class session
{
public:
	session( boost::asio::io_service & _service );

public:
	void accept();
	void connect( const boost::asio::ip::tcp::endpoint & _endpoint );
	void procces();

public:
	boost::asio::ip::tcp::socket & get_socket();

	stream_read * get_streamIn();
	stream_write * get_streamOut();

protected:
	void handle_connect( const boost::system::error_code & _ec );

protected:
	void handle_write_stream( const boost::system::error_code & _ec );

protected:
	void handle_read_size( const boost::system::error_code & _ec, std::size_t * _size );
	void handle_read_blob( const boost::system::error_code & _ec, TBlobject::value_type * _blob );

protected:
	void run();

public:
	virtual void dispatch_message( std::size_t _size ) = 0;

protected:
	stream_write * m_streamWrite;
	stream_write * m_streamSend;

	stream_read * m_streamIn;

	boost::asio::ip::tcp::socket m_socket;
};