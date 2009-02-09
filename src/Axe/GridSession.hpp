#	pragma once

#	include "Session.hpp"

namespace Axe
{
	class GridSession
		: public Session
	{
	public:
		GridSession( boost::asio::io_service & _service, const GridPtr & _rt );

	public:
		ArchiveWrite & beginResponse( std::size_t _responseId );

	public:
		void dispatchMessage( ArchiveRead & _ar, std::size_t _size ) override;
		void permissionVerify( ArchiveRead & _ar, std::size_t _size ) override;

	protected:
		GridPtr m_grid;
	};

	typedef AxeHandle<GridSession> GridSessionPtr;
}