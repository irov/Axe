#	include "pch.hpp"

#	include <Axe/GridSession.hpp>
#	include <Axe/Grid.hpp>

#	include <AxeProtocols/GridManager.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	GridSession::GridSession( boost::asio::io_service & _service, const HostPtr & _host, const ConnectionCachePtr & _connectionCache )
		: HostSession(_service, _host, _connectionCache)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void GridSession::permissionVerify( ArchiveDispatcher & _ar, std::size_t _size )
	{
		GridPtr grid = AxeUtil::handleCast<GridPtr>( m_host );

		const Proxy_GridManagerPtr & gridManager = grid->getGridManager();

		ArchiveInvocation & ar = this->beginConnect( true );
		ar << gridManager;

		this->process();

		this->run();
	}
}