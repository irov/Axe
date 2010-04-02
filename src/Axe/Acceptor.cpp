#	include "pch.hpp"

#	include "Acceptor.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Acceptor::Acceptor( boost::asio::io_service & _service, const boost::asio::ip::tcp::endpoint & _endpoint )
		: Service(_service)
		, m_acceptor(_service, _endpoint)
		, m_endpoint(_endpoint)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	const boost::asio::ip::tcp::endpoint & Acceptor::getEndpoint() const
	{
		return m_endpoint;
	}
	//////////////////////////////////////////////////////////////////////////
	void Acceptor::accept()
	{
		SessionPtr session = this->makeSession();

		const SocketPtr & socket = session->getSocket();

		boost::asio::ip::tcp::socket & asio_socket = socket->getAsioSocket();

		m_acceptor.async_accept( asio_socket
			, boost::bind( &Acceptor::acceptHandle, handlePtr(this), boost::asio::placeholders::error, session )
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Acceptor::acceptHandle( const boost::system::error_code & _ec, const SessionPtr & _session )
	{
		m_sessions.push_back( _session );

		_session->accept();

		this->accept();
	}
}