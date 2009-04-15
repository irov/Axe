#	pragma once

#	include <Axe/Dispatcher.hpp>
#	include <Axe/Connection.hpp>

#	include <Axe/EndpointCache.hpp>

namespace Axe
{
	class Invocation
		: public Dispatcher
		, public Connection
		, public EndpointCallback
	{
	public:
		Invocation( boost::asio::io_service & _service, std::size_t _hostId, const EndpointCachePtr & _endpointCache, const ConnectionCachePtr & _connectionCache );

	public:
		void processMessage() override;

	protected:
		ArchiveInvocation & connect( const boost::asio::ip::tcp::endpoint & _endpoint );

	protected:
		void handleConnect( const boost::system::error_code & _ec );

		void handleReadConnectSize( const boost::system::error_code & _ec, std::size_t * _size );
		void handleReadConnect( const boost::system::error_code & _ec, AxeUtil::Archive::value_type * _blob );

	protected:
		void onEndpoint( const boost::asio::ip::tcp::endpoint & _endpoint ) override;

	protected:
		virtual void connectionSuccessful( ArchiveDispatcher & _ar, std::size_t _size ) = 0;
		virtual void connectionFailed( ArchiveDispatcher & _ar, std::size_t _size ) = 0;

	protected:
		EndpointCachePtr m_endpointCache;
		ArchiveInvocation m_permission;
	};

	typedef AxeHandle<Invocation> InvocationPtr;
}