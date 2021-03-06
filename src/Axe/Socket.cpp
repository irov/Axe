#	include "pch.hpp"

#	include "Socket.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Socket::Socket( boost::asio::io_service & _service )
		: m_socket(_service)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	boost::asio::ip::tcp::socket & Socket::getAsioSocket() const
	{
		return m_socket;
	}
	//////////////////////////////////////////////////////////////////////////
	void Socket::connect( const boost::asio::ip::tcp::endpoint & _endpoint, const FSocketConnectResponse & _response )
	{
		m_socket.async_connect( _endpoint, _response );
	}
	//////////////////////////////////////////////////////////////////////////
	void Socket::accept( boost::asio::ip::tcp::acceptor & _aceeptor, const FSocketAcceptResponse & _response )
	{
		_aceeptor.async_accept( m_socket, _response	);
	}
	//////////////////////////////////////////////////////////////////////////
	void Socket::close()
	{
		m_socket.close();
	}
	//////////////////////////////////////////////////////////////////////////
	bool Socket::is_open() const
	{
		return m_socket.is_open();
	}
	//////////////////////////////////////////////////////////////////////////
	static bool s_handleReadCondition( const boost::system::error_code & _ec, std::size_t _read, std::size_t _wait )
	{
		return ( _read >= _wait );
	}
	//////////////////////////////////////////////////////////////////////////
	void Socket::read( void * _buffer, std::size_t _size, const FSocketReadResponse & _response )
	{
		boost::asio::async_read( m_socket
			, boost::asio::buffer( _buffer, _size )
			, boost::bind( &s_handleReadCondition, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, _size )
			, _response
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Socket::write( const void * _buffer, std::size_t _size, const FSocketWriteResponse & _response )
	{
		boost::asio::async_write( m_socket
			, boost::asio::buffer( _buffer, _size )
			, _response
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Socket::read_arhive( AxeUtil::Archive & _ar, const FSocketReadResponse & _response )
	{
		this->read( &_ar.front(), _ar.size(), _response );
	}
	//////////////////////////////////////////////////////////////////////////
	void Socket::write_arhive( const AxeUtil::Archive & _ar, const FSocketWriteResponse & _response )
	{
		this->write( &_ar.front(), _ar.size(), _response );
	}

}