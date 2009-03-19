#	include "pch.hpp"

#	include <Axe/GridConnection.hpp>

#	include <Axe/Session.hpp>
#	include <Axe/Adapter.hpp>
#	include <Axe/Response.hpp>

#	include <Axe/ArchiveWrite.hpp>
#	include <Axe/ArchiveRead.hpp>

#	include <AxeProtocols/Player.hpp>

namespace Axe
{
	const std::size_t grid_host_id = 0;
	//////////////////////////////////////////////////////////////////////////
	GridConnection::GridConnection( boost::asio::io_service & _service, const EndpointCachePtr & _endpointCache, const ConnectionCachePtr & _connectionCache, const GridConnectResponsePtr & _connectResponse )
		: AdapterConnection( _service, grid_host_id, _endpointCache, _connectionCache )
		, m_connectResponse(_connectResponse)
	{
		m_connectionCache->addConnection( grid_host_id, this );
	}
	//////////////////////////////////////////////////////////////////////////
	void GridConnection::connect( const boost::asio::ip::tcp::endpoint & _endpoint )
	{
		Invocation::connect( _endpoint );
	}
	//////////////////////////////////////////////////////////////////////////
	void GridConnection::connectionSuccessful( ArchiveRead & _ar, std::size_t _size )
	{
		Proxy_GridManagerPtr gridManager = 
			makeProxy<Proxy_GridManagerPtr>( _ar );

		m_connectResponse->connectSuccessful( gridManager );
	}
	//////////////////////////////////////////////////////////////////////////
	void GridConnection::connectionFailed( ArchiveRead & _ar, std::size_t _size )
	{
		m_connectResponse->connectFailed();
	}
}