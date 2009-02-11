#	pragma once

#	include "Invocation.hpp"

#	include "AdapterConnectResponse.hpp"

namespace Axe
{
	class ArchiveRead;

	typedef AxeHandle<class Response> ResponsePtr;

	class GridConnection
		: public Invocation
	{
	public:
		GridConnection( boost::asio::io_service & _service, const AdapterConnectResponsePtr & _connectResponse );

	public:
		void registerAdapter( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name );

	protected:
		ArchiveWrite & beginMessage( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response ) override;

	protected:
		void dispatchMessage( ArchiveRead & _read, std::size_t _size ) override;

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