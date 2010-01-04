#	include "pch.hpp"

#	include <Axe/Grid.hpp>
#	include <Axe/GridSession.hpp>
#	include <Axe/AdapterConnection.hpp>

#	include <Axe/GridManager.hpp>

namespace Axe
{
	const std::size_t grid_host_id = 0;
	//////////////////////////////////////////////////////////////////////////
	Grid::Grid( boost::asio::io_service & _service, const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name )
		: Host(_service, new ConnectionCache(this), _endpoint, _name, grid_host_id)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	const ProxyPtr & Grid::addGridManager( const ServantPtr & _servant )
	{
		m_gridManagerPrx = this->addServant( 0, _servant );

		return m_gridManagerPrx;
	}
	//////////////////////////////////////////////////////////////////////////
	const ProxyPtr & Grid::getGridManager() const
	{
		return m_gridManagerPrx;
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
