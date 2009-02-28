#	pragma once

#	include "Dispatcher.hpp"
#	include "Connection.hpp"

#	include "EndpointCache.hpp"

namespace Axe
{
	class Invocation
		: public Dispatcher
		, public Connection
		, public EndpointCallback
	{
	public:
		Invocation( boost::asio::io_service & _service, std::size_t _hostId, const EndpointCachePtr & _endpointCache );

	public:
		void processMessage() override;

	protected:
		ArchiveWrite & connect( const boost::asio::ip::tcp::endpoint & _endpoint );

	protected:
		void handleConnectRead( const boost::system::error_code & _ec );
		void handleConnectProcess( const boost::system::error_code & _ec );

		void handleReadConnectSize( const boost::system::error_code & _ec, std::size_t * _size );
		void handleReadConnect( const boost::system::error_code & _ec, Archive::value_type * _blob );

	protected:
		void onEndpoint( const boost::asio::ip::tcp::endpoint & _endpoint ) override;

	public:
		virtual void connectionSuccessful( ArchiveRead & _ar, std::size_t _size ) = 0;
		virtual void connectionFailed( ArchiveRead & _ar, std::size_t _size ) = 0;

	protected:
		EndpointCachePtr m_endpointCache;
	};
}