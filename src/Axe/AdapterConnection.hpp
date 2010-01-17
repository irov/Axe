#	pragma once


#	include <Axe/Invocation.hpp>

#	include <Axe/ConnectionCache.hpp>

namespace Axe
{
	class ArchiveDispatcher;

	typedef AxeHandle<class Response> ResponsePtr;

	class AdapterConnection
		: public Invocation
	{
	public:
		AdapterConnection( boost::asio::io_service & _service, std::size_t m_adapterId, const EndpointCachePtr & _endpointCache, const ConnectionCachePtr & _connectionCache );

	public:
		ArchiveInvocation & beginMessage( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response ) override;		

	public:
		void dispatchMessage( ArchiveDispatcher & _ar, std::size_t _size ) override;
		
		void connectionSuccessful( ArchiveDispatcher & _ar, std::size_t _size ) override;
		void connectionFailed( ArchiveDispatcher & _ar, std::size_t _size ) override;

	protected:
		std::size_t addDispatch( const ResponsePtr & _response );
		void writeBody( ArchiveInvocation & _archive, std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response );

	protected:
		std::size_t m_messageEnum;

		typedef std::map<std::size_t, ResponsePtr> TMapResponse;
		TMapResponse m_dispatch;
	};

	typedef AxeHandle<AdapterConnection> AdapterConnectionPtr;
}