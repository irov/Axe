#	include "pch.hpp"

#	include "host.hpp"

#	include "session.hpp"

host::host( boost::asio::io_service & _service, const boost::asio::ip::tcp::endpoint & _endpoint )
: m_acceptor(_service, _endpoint)
{

}

void host::run()
{
	session * sn = this->make_session();

	m_acceptor.async_accept( sn->get_socket()
		, boost::bind( &host::handle_accept, this, boost::asio::placeholders::error, sn )
		);
}

void host::handle_accept( const boost::system::error_code & _ec, session * _sn )
{
	_sn->accept();

	this->run();
}