#	pragma once

#	include <Axe/Connection.hpp>
#	include <Axe/Dispatcher.hpp>

#	include <Axe/ConnectionCache.hpp>
#	include <Axe/EndpointCache.hpp>

namespace Axe
{
	class ArchiveDispatcher;

	typedef AxeHandle<class Response> ResponsePtr;

	class AdapterConnection
		: public Connection
		, public Dispatcher
	{
	public:
		AdapterConnection( const SocketPtr & _socket, const ConnectionCachePtr & _connectionCache, std::size_t _adapterId, const EndpointCachePtr & _endpointCache );

	public:
		ArchiveInvocation & beginMessage( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response ) override;

	public:
		void dispatchMessage( ArchiveDispatcher & _ar, std::size_t _size ) override;
		
	protected:
		void write( ArchiveInvocation & _ar ) const override;

	protected:
		void _reconnect() override;

	protected:
		void onEndpoint( const boost::asio::ip::tcp::endpoint & _endpoint );

	protected:
		std::size_t m_adapterId;
		EndpointCachePtr m_endpointCache;
	};

	typedef AxeHandle<AdapterConnection> AdapterConnectionPtr;
}