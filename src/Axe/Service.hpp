#	pragma once

#	include "Shared.hpp"

namespace Axe
{
	typedef AxeHandle<class Session> SessionPtr;

	class Service
		: virtual public Shared
	{
	public:
		Service( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name );

	public:
		void run();

	public:
		const std::string & getName() const;
		const boost::asio::ip::tcp::endpoint & getEndpoint() const;

	protected:
		virtual SessionPtr makeSession() = 0;

	protected:
		void accept();

	private:
		void acceptHandle( const boost::system::error_code & _ec, const SessionPtr & _sn );

	protected:
		boost::asio::ip::tcp::endpoint m_endpoint;

		boost::asio::io_service m_service;
		boost::asio::ip::tcp::acceptor m_acceptor;

		std::string m_name;

		typedef std::list<SessionPtr> TListSessions;
		TListSessions m_sessions;
	};
}