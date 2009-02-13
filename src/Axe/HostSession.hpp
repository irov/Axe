#	pragma once

#	include "Session.hpp"
#	include "Host.hpp"

namespace Axe
{
	class ArchiveWrite;

	class HostSession
		: public Session
	{
	public:
		HostSession( boost::asio::io_service & _service, const HostPtr & _host );

	public:
		void dispatchMessage( ArchiveRead & _ar, std::size_t _size ) override;

	protected:
		HostPtr m_host;
	};

	typedef AxeHandle<HostSession> HostSessionPtr;
}