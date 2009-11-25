#	pragma once

#	include <Axe/HostSession.hpp>

namespace Axe
{
	class GridSession
		: public HostSession
	{
	public:
		GridSession( boost::asio::io_service & _service, const HostPtr & _host, const ConnectionCachePtr & _connectionCache );

	public:
		void permissionVerify( ArchiveDispatcher & _ar, std::size_t _size ) override;
	};

	typedef AxeHandle<GridSession> GridSessionPtr;
}