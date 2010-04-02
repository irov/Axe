#	pragma once

#	include <AxeUtil\Shared.hpp>

#	include <Axe/Service.hpp>
#	include <Axe/Session.hpp>

namespace Axe
{
	class Acceptor
		: public Service
	{
	public:
		Acceptor( boost::asio::io_service & _service, const boost::asio::ip::tcp::endpoint & _endpoint );

	public:
		const boost::asio::ip::tcp::endpoint & getEndpoint() const;

	public:
		void accept();

	protected:
		virtual SessionPtr makeSession() = 0;

	protected:
		void acceptHandle( const boost::system::error_code & _ec, const SessionPtr & _session );

	protected:
		boost::asio::ip::tcp::acceptor m_acceptor;
		boost::asio::ip::tcp::endpoint m_endpoint;

		typedef std::list<SessionPtr> TListSessions;
		TListSessions m_sessions;
	};

	typedef AxeHandle<Acceptor> AcceptorPtr;
}