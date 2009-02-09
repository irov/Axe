#	include "pch.hpp"

#	include "Grid.hpp"
#	include "GridSession.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Grid::Grid( const boost::asio::ip::tcp::endpoint & _endpoint )
		: Host( _endpoint)
	{

	}
	//////////////////////////////////////////////////////////////////////////
	void Grid::initialize()
	{
		this->run();
	}
	//////////////////////////////////////////////////////////////////////////
	SessionPtr Grid::makeSession()
	{
		GridSessionPtr session = new GridSession( m_service, this );

		return session;
	}
}
