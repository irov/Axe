#	include "pch.hpp"

#	include "GridConnection.hpp"

#	include "Session.hpp"
#	include "Adapter.hpp"
#	include "Response.hpp"

#	include "ArchiveWrite.hpp"
#	include "ArchiveRead.hpp"

#	include "AxeProtocols/Player.hpp"

namespace Axe
{
	const std::size_t grid_endpoint_id = 0;
	//////////////////////////////////////////////////////////////////////////
	GridConnection::GridConnection( boost::asio::io_service & _service, const EndpointCachePtr & _endpointCache, const ConnectionCachePtr & _connectionCache, const GridConnectResponsePtr & _connectResponse )
		: AdapterConnection( _service, grid_endpoint_id, _endpointCache, _connectionCache )
		, m_connectResponse(_connectResponse)
	{
		m_connectionCache->addConnection( grid_endpoint_id, this );
	}
	//////////////////////////////////////////////////////////////////////////
	void GridConnection::connect( const boost::asio::ip::tcp::endpoint & _endpoint )
	{
		ArchiveWrite & ar = Invocation::connect( _endpoint );
		
		//ar.write( 0 );

		Invocation::processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	void GridConnection::connectionSuccessful( ArchiveRead & _ar, std::size_t _size )
	{
		Proxy_GridManagerPtr gridManager = 
			makeProxy<Proxy_GridManagerPtr>( _ar, m_connectionCache );

		m_connectResponse->connectSuccessful( gridManager );
	}
	//////////////////////////////////////////////////////////////////////////
	void GridConnection::connectionFailed( ArchiveRead & _ar, std::size_t _size )
	{
		m_connectResponse->connectFailed();
	}
}