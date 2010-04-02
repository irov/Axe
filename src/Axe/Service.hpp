#	pragma once

#	include <AxeUtil\Shared.hpp>

namespace Axe
{
	class Service
		: virtual public AxeUtil::Shared
	{
	public:
		Service( boost::asio::io_service & _service );

	public:
		void run();

	protected:
		boost::asio::io_service & m_service;
	};
}