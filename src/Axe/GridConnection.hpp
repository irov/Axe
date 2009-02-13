#	pragma once

#	include "AdapterConnection.hpp"

#	include "GridConnectResponse.hpp"

namespace Axe
{
	class ArchiveRead;

	typedef AxeHandle<class Response> ResponsePtr;

	class GridConnection
		: public AdapterConnection
	{
	public:
		GridConnection( boost::asio::io_service & _service, const ConnectionCachePtr & _connectionCache, const GridConnectResponsePtr & _connectResponse );

	protected:
		void connectionSuccessful( ArchiveRead & _ar, std::size_t _size ) override;
		void connectionFailed( ArchiveRead & _ar, std::size_t _size ) override;

	protected:
		GridConnectResponsePtr m_connectResponse;
	};

	typedef AxeHandle<GridConnection> GridConnectionPtr;
}