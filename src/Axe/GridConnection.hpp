#	pragma once

#	include <Axe/AdapterConnection.hpp>

#	include <Axe/GridConnectResponse.hpp>

namespace Axe
{
	class ArchiveDispatcher;

	typedef AxeHandle<class Response> ResponsePtr;

	class GridConnection
		: public AdapterConnection
	{
	public:
		GridConnection( boost::asio::io_service & _service, const EndpointCachePtr & _endpointCache, const ConnectionCachePtr & _connectionCache, const GridConnectResponsePtr & _connectResponse );

	public:
		void connect( const boost::asio::ip::tcp::endpoint & _endpoint );

	protected:
		void connectionSuccessful( ArchiveDispatcher & _ar, std::size_t _size ) override;
		void connectionFailed( ArchiveDispatcher & _ar, std::size_t _size ) override;

	protected:
		GridConnectResponsePtr m_connectResponse;
	};

	typedef AxeHandle<GridConnection> GridConnectionPtr;
}