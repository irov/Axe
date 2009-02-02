#	pragma once

#	include "Host.hpp"

namespace Axe
{
	class Grid
		: public Host
	{	
	public:
		Grid( boost::asio::io_service & _service, const boost::asio::ip::tcp::endpoint & _endpoint );

	public:
		void initialize();

	protected:
		SessionPtr makeSession() override;

	};

	typedef AxeHandle<Grid> GridPtr;
}
