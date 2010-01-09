#	include "pch.hpp"

#	include <Axe/Grid.hpp>
#	include <Axe/GridSession.hpp>

#	include <Axe/Communicator.hpp>

#	include <Axe/AdapterConnection.hpp>

#	include <AxeProtocols/GridManager.hpp>

namespace Axe
{
	const std::size_t grid_host_id = 0;
	//////////////////////////////////////////////////////////////////////////
	Grid::Grid( const CommunicatorPtr & _communicator, const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name )
		: Host(_communicator, _endpoint, _name, grid_host_id)
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
		const ConnectionCachePtr & connectionCache = m_communicator->getConnectionCache();

		GridSessionPtr session = new GridSession( m_service, this, connectionCache );

		return session;
	}
}
