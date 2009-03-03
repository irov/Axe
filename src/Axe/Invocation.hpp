#	pragma once

#	include "Dispatcher.hpp"
#	include "Connection.hpp"

#	include "EndpointCache.hpp"

namespace Axe
{
	class ConnectCallback
		: virtual public Shared
	{
	public:
		virtual void connectionSuccessful( ArchiveRead & _ar, std::size_t _size ) = 0;
		virtual void connectionFailed( ArchiveRead & _ar, std::size_t _size ) = 0;
	};

	typedef AxeHandle<ConnectCallback> ConnectCallbackPtr;

	class Invocation
		: public Dispatcher
		, public Connection
		, public EndpointCallback
		, public ConnectCallback
	{
	public:
		Invocation( boost::asio::io_service & _service, std::size_t _hostId, const EndpointCachePtr & _endpointCache, const ConnectionCachePtr & _connectionCache );

	public:
		void processMessage() override;

	protected:
		ArchiveWrite & connect( const boost::asio::ip::tcp::endpoint & _endpoint );

	protected:
		void handleConnect( const boost::system::error_code & _ec, const ConnectCallbackPtr & _cb );

		void handleReadConnectSize( const boost::system::error_code & _ec, std::size_t * _size, const ConnectCallbackPtr & _cb );
		void handleReadConnect( const boost::system::error_code & _ec, Archive::value_type * _blob, const ConnectCallbackPtr & _cb );

	protected:
		void onEndpoint( const boost::asio::ip::tcp::endpoint & _endpoint ) override;

	protected:
		void connect_( const boost::asio::ip::tcp::endpoint & _endpoint, const ConnectCallbackPtr & _cb );

	protected:
		EndpointCachePtr m_endpointCache;
		ArchiveWrite m_permission;
	};

	typedef AxeHandle<Invocation> InvocationPtr;
}