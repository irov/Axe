#	include "pch.hpp"

#	include "GridConnection.hpp"

#	include "Session.hpp"
#	include "Adapter.hpp"
#	include "Response.hpp"

#	include "ArchiveWrite.hpp"
#	include "ArchiveRead.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	GridConnection::GridConnection( boost::asio::io_service & _service, const ConnectionCachePtr & _connectionCache, const GridConnectResponsePtr & _connectResponse )
		: AdapterConnection( _service, _connectionCache, 0 )
		, m_connectResponse(_connectResponse)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void GridConnection::connectionSuccessful( ArchiveRead & _ar, std::size_t _size )
	{
		Proxy_GridManagerPtr gridManager;

		_ar.read( gridManager );

		m_connectResponse->connectSuccessful( gridManager );
	}
	//////////////////////////////////////////////////////////////////////////
	void GridConnection::connectionFailed( ArchiveRead & _ar, std::size_t _size )
	{
		m_connectResponse->connectFailed();
	}
}