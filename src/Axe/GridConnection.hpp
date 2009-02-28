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
		GridConnection( boost::asio::io_service & _service, const EndpointCachePtr & _endpointCache, const ConnectionCachePtr & _connectionCache, const GridConnectResponsePtr & _connectResponse );

	public:
		void connect( const boost::asio::ip::tcp::endpoint & _endpoint );

	protected:
		void connectionSuccessful( ArchiveRead & _ar, std::size_t _size ) override;
		void connectionFailed( ArchiveRead & _ar, std::size_t _size ) override;

	protected:
		GridConnectResponsePtr m_connectResponse;
	};

	typedef AxeHandle<GridConnection> GridConnectionPtr;
}