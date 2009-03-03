#	include "pch.hpp"

#	include "GridSession.hpp"
#	include "Grid.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	GridSession::GridSession( boost::asio::io_service & _service, const HostPtr & _host, const ConnectionCachePtr & _connectionCache )
		: HostSession(_service, _host, _connectionCache)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void GridSession::permissionVerify( ArchiveRead & _ar, std::size_t _size )
	{
		GridPtr grid = handleCast<GridPtr>( m_host );

		const Proxy_GridManagerPtr & gridManager = grid->getGridManager();

		ArchiveWrite & ar = this->beginConnect( true );
		ar.write( gridManager );

		this->process();

		this->run();
	}
}