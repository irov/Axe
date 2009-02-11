#	include "pch.hpp"

#	include "GridSession.hpp"
#	include "Grid.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	GridSession::GridSession( boost::asio::io_service & _service, const GridPtr & _grid )
		: Session(_service)
		, m_grid(_grid)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void GridSession::dispatchMessage( ArchiveRead & _ar, std::size_t _size )
	{
		//Empty
	}
	//////////////////////////////////////////////////////////////////////////
	void GridSession::permissionVerify( ArchiveRead & _ar, std::size_t _size )
	{
		std::string name;

		_ar.readString( name );

		std::size_t id = m_grid->addAdapter( name );

		ArchiveWrite & ar = this->beginConnect( true );
		ar.write( id );

		this->process();
	}
}