#	include "pch.hpp"

#	include "Service.hpp"

#	include "Session.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Service::Service( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name )
		: m_endpoint(_endpoint)
		, m_acceptor(m_service, _endpoint)
		, m_name(_name)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Service::run()
	{
		m_service.run();
	}
	//////////////////////////////////////////////////////////////////////////
	const std::string & Service::getName() const
	{
		return m_name;
	}
	//////////////////////////////////////////////////////////////////////////
	const boost::asio::ip::tcp::endpoint & Service::getEndpoint() const
	{
		return m_endpoint;
	}
	//////////////////////////////////////////////////////////////////////////
	void Service::accept()
	{
		SessionPtr session = this->makeSession();

		m_acceptor.async_accept( session->getSocket()
			, boost::bind( &Service::acceptHandle, intrusivePtr(this), boost::asio::placeholders::error, session )
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Service::acceptHandle( const boost::system::error_code & _ec, const SessionPtr & _session )
	{
		m_sessions.push_back( _session );

		_session->accept();

		this->accept();
	}
}