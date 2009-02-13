#	pragma once

#	include "AdapterConnection.hpp"

#	include "AdapterConnectResponse.hpp"

namespace Axe
{
	class ArchiveRead;

	typedef AxeHandle<class Response> ResponsePtr;

	class GridConnection
		: public AdapterConnection
	{
	public:
		GridConnection( boost::asio::io_service & _service, const ConnectionCachePtr & _connectionCache, const AdapterConnectResponsePtr & _connectResponse );

	public:
		void registerAdapter( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name );

	protected:
		void connectionSuccessful( ArchiveRead & _ar, std::size_t _size ) override;
		void connectionFailed( ArchiveRead & _ar, std::size_t _size ) override;

	protected:
		std::size_t addDispatch( const ResponsePtr & _response );
		void writeBody( ArchiveWrite & _archive, std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response );

	protected:
		AdapterConnectResponsePtr m_connectResponse;
	};

	typedef AxeHandle<GridConnection> GridConnectionPtr;
}