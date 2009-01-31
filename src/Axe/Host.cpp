#	include "pch.hpp"

#	include "Host.hpp"

#	include "Session.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Host::Host( const boost::asio::ip::tcp::endpoint & _endpoint )
		: m_acceptor(m_service, _endpoint)
	{

	}
	//////////////////////////////////////////////////////////////////////////
	void Host::run()
	{
		SessionPtr session = this->makeSession();

		m_acceptor.async_accept( session->getSocket()
			, boost::bind( &Host::accept, this, boost::asio::placeholders::error, session )
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Host::accept( const boost::system::error_code & _ec, const SessionPtr & _session )
	{
		_session->accept();

		this->run();
	}
}