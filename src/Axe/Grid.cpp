#	include "pch.hpp"

#	include "Grid.hpp"
#	include "GridSession.hpp"
#	include "AdapterConnection.hpp"

#	include "GridManager.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Grid::Grid( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name )
		: Host(_endpoint, _name)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Grid::initialize()
	{
		m_gridManager = new GridManager();

		m_gridManager->setServantId(0);

		m_servants.insert( std::make_pair( 0, m_gridManager ) );

		this->accept();
	}
	//////////////////////////////////////////////////////////////////////////
	const Servant_GridManagerPtr & Grid::getGridManager() const
	{
		return m_gridManager;
	}
	//////////////////////////////////////////////////////////////////////////
	SessionPtr Grid::makeSession()
	{
		GridSessionPtr session = new GridSession( m_service, this );

		return session;
	}
	//////////////////////////////////////////////////////////////////////////
	ConnectionPtr Grid::createConnection( std::size_t _hostId )
	{
		AdapterConnectionPtr connection = new AdapterConnection( m_acceptor.get_io_service(), m_connectionCache, _hostId );

		return connection;
	}
}
