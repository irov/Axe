#	pragma once

#	include "Shared.hpp"

namespace Axe
{
	typedef AxeHandle<class Session> SessionPtr;

	class Host
		: public Shared
	{
	public:
		Host( boost::asio::io_service & _service, const boost::asio::ip::tcp::endpoint & _endpoint );

	protected:
		virtual SessionPtr makeSession() = 0;

	protected:
		void run();

	private:
		void accept( const boost::system::error_code & _ec, const SessionPtr & _sn );

	protected:
		boost::asio::ip::tcp::acceptor m_acceptor;
	};
}