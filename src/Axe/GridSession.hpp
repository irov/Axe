#	pragma once

#	include "AdapterSession.hpp"

namespace Axe
{
	typedef AxeHandle<class Grid> GridPtr;

	class GridSession
		: public AdapterSession
	{
	public:
		GridSession( boost::asio::io_service & _service, const GridPtr & _grid );

	public:
		void permissionVerify( ArchiveRead & _ar, std::size_t _size ) override;
	};

	typedef AxeHandle<GridSession> GridSessionPtr;
}