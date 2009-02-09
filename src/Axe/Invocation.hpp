#	pragma once

#	include "Dispatcher.hpp"
#	include "Connection.hpp"

namespace Axe
{
	class Invocation
		: public Dispatcher
		, public Connection
	{
	public:
		Invocation( boost::asio::io_service & _service, std::size_t _endpointId );

	public:
		ArchiveWrite & connect( const boost::asio::ip::tcp::endpoint & _endpoint );

	public:
		void processMessage() override;

	protected:
		void handleConnect( const boost::system::error_code & _ec );

		void handleReadConnectSize( const boost::system::error_code & _ec, std::size_t * _size );
		void handleReadConnect( const boost::system::error_code & _ec, Archive::value_type * _blob );

	public:
		virtual void connectionSuccessful( ArchiveRead & _ar, std::size_t _size ) = 0;
		virtual void connectionFailed( ArchiveRead & _ar, std::size_t _size ) = 0;
	};
}