#	include "pch.hpp"

#	include "session_connection.hpp"

session_connection::session_connection( boost::asio::io_service & _service )
: session( _service )
{

}

void session_connection::procces()
{
	session::procces();
}