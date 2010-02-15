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
	void Socket::connect( const boost::asio::ip::tcp::endpoint & _endpoint, const SocketConnectResponsePtr & _response )
	{
		m_socket.async_connect( _endpoint
			, boost::bind( &SocketConnectResponse::onConnect, _response, boost::asio::placeholders::error ) 
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Socket::accept( boost::asio::ip::tcp::acceptor & _aceeptor, const SocketAcceptResponsePtr & _response )
	{
		_aceeptor.async_accept( m_socket
			, boost::bind( &SocketAcceptResponse::onAccept, _response, boost::asio::placeholders::error )
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Socket::close()
	{
		m_socket.close();
	}
	//////////////////////////////////////////////////////////////////////////
	bool Socket::handleReadCondition( const boost::system::error_code & _ec, std::size_t _read, std::size_t _wait )
	{
		return ( _read >= _wait );
	}

}