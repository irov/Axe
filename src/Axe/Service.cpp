#	include "pch.hpp"

#	include <Axe/Service.hpp>

#	include <Axe/Session.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Service::Service( boost::asio::io_service & _service )
		: m_service(_service)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Service::run()
	{
		m_service.run();
	}
}