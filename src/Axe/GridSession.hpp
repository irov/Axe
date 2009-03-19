#	pragma once

#	include <Axe/HostSession.hpp>

namespace Axe
{
	typedef AxeHandle<class Grid> GridPtr;

	class GridSession
		: public HostSession
	{
	public:
		GridSession( boost::asio::io_service & _service, const HostPtr & _host, const ConnectionCachePtr & _connectionCache );

	public:
		void permissionVerify( ArchiveRead & _ar, std::size_t _size ) override;
	};

	typedef AxeHandle<GridSession> GridSessionPtr;
}