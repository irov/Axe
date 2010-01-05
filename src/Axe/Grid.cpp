#	include "pch.hpp"

#	include <Axe/Grid.hpp>
#	include <Axe/GridSession.hpp>
#	include <Axe/AdapterConnection.hpp>

#	include <AxeProtocols/GridManager.hpp>

namespace Axe
{
	const std::size_t grid_host_id = 0;
	//////////////////////////////////////////////////////////////////////////
	Grid::Grid( boost::asio::io_service & _service, const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name )
		: Host(_service, new ConnectionCache(this), _endpoint, _name, grid_host_id)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	const Proxy_GridManagerPtr & Grid::addGridManager( const Servant_GridManagerPtr & _servant )
	{
		ProxyPtr basePrx = this->addServant( 0, _servant );

		m_gridManager = uncheckedCast<Proxy_GridManagerPtr>(basePrx);

		return m_gridManager;
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
	ConnectionPtr Grid::createConnection( std::size_t _hostId )
	{
		AdapterConnectionPtr connection = new AdapterConnection( m_service, _hostId, 0, m_connectionCache );

		return connection;
	}
}
