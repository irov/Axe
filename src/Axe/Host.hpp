#	pragma once

#	include "Shared.hpp"

namespace Axe
{
	typedef AxeHandle<class Session> SessionPtr;

	class Host
		: virtual public Shared
	{
	public:
		Host( const boost::asio::ip::tcp::endpoint & _endpoint );

	public:
		void run();

	protected:
		virtual SessionPtr makeSession() = 0;

	protected:
		void accept();

	private:
		void acceptHandle( const boost::system::error_code & _ec, const SessionPtr & _sn );

	protected:
		boost::asio::io_service m_service;
		boost::asio::ip::tcp::acceptor m_acceptor;

		typedef std::list<SessionPtr> TListSessions;
		TListSessions m_sessions;
	};
}