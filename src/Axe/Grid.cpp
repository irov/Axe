#	include "pch.hpp"

#	include "Grid.hpp"
#	include "GridSession.hpp"
#	include "AdapterConnection.hpp"

#	include "GridManager.hpp"

namespace Axe
{
	const std::size_t grid_host_id = 0;
	//////////////////////////////////////////////////////////////////////////
	Grid::Grid( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name )
		: Host(m_service, new ConnectionCache(this), _endpoint, _name, grid_host_id)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Grid::initialize()
	{
		GridManagerPtr servant = new GridManager();

		servant->setServantId(0);

		ProxyPtr base = this->addServant( servant );

		m_gridManager 
			= uncheckedCast<Proxy_GridManagerPtr>(base);

		this->accept();
	}
	//////////////////////////////////////////////////////////////////////////
	const Proxy_GridManagerPtr & Grid::getGridManager() const
	{
		return m_gridManager;
	}
	//////////////////////////////////////////////////////////////////////////
	SessionPtr Grid::makeSession()
	{
		GridSessionPtr session = new GridSession( m_service, this, m_connectionCache );

		return session;
	}
	//////////////////////////////////////////////////////////////////////////
	ConnectionPtr Grid::createConnection( std::size_t _hostId, const ConnectionCachePtr & _connectionCache )
	{
		AdapterConnectionPtr connection = new AdapterConnection( m_service, _hostId, 0, _connectionCache );

		return connection;
	}
}
