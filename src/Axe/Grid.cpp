#	include "pch.hpp"

#	include "Grid.hpp"
#	include "GridSession.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Grid::Grid( const boost::asio::ip::tcp::endpoint & _endpoint )
		: Host(_endpoint)
		, m_enumeratorID(0)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Grid::initialize()
	{
		this->accept();
	}
	//////////////////////////////////////////////////////////////////////////
	SessionPtr Grid::makeSession()
	{
		GridSessionPtr session = new GridSession( m_service, this );

		return session;
	}
}
