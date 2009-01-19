#	pragma once

#	include "Connection.hpp"
#	include "Session.hpp"

namespace Axe
{
	class SessionConnection
		: public Connection
		, public Session
	{
	public:
		SessionConnection( boost::asio::io_service & _service );

	public:
		void procces() override;
	};
}