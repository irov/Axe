#	include "pch.hpp"

#	include "GridSession.hpp"
#	include "Grid.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	GridSession::GridSession( boost::asio::io_service & _service, const HostPtr & _host )
		: HostSession(_service, _host)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void GridSession::permissionVerify( ArchiveRead & _ar, std::size_t _size )
	{
		std::string name;

		_ar.readString( name );

		GridPtr grid = handleCast<GridPtr>( m_host );

		const Servant_GridManagerPtr & gridManager = grid->getGridManager();

		ArchiveWrite & ar = this->beginConnect( true );
		ar.write( gridManager );

		this->process();
	}
}