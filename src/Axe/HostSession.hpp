#	pragma once

#	include <Axe/Session.hpp>
#	include <Axe/Host.hpp>

namespace Axe
{
	class ArchiveWrite;

	class HostSession
		: public Session
	{
	public:
		HostSession( boost::asio::io_service & _service, const HostPtr & _host, const ConnectionCachePtr & _connectionCache );

	public:
		void dispatchMessage( ArchiveRead & _ar, std::size_t _size ) override;

	protected:
		HostPtr m_host;
	};

	typedef AxeHandle<HostSession> HostSessionPtr;
}