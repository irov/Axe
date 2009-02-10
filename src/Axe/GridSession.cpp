#	include "pch.hpp"

#	include "GridSession.hpp"
#	include "Grid.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	GridSession::GridSession( boost::asio::io_service & _service, const GridPtr & _grid )
		: AdapterSession(_service, _grid)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void GridSession::permissionVerify( ArchiveRead & _ar, std::size_t _size )
	{
		std::string name;

		_ar.readString( name );

		GridPtr grid = handleCast<GridPtr>( m_adapter );

		std::size_t id = grid->addAdapter( name );

		ArchiveWrite & ar = this->beginConnect( true );
		ar.write( id );

		this->process();
	}
}