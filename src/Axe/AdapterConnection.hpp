#	pragma once


#	include "Invocation.hpp"

#	include "ConnectionCache.hpp"

namespace Axe
{
	class ArchiveRead;

	typedef AxeHandle<class Response> ResponsePtr;

	class AdapterConnection
		: public Invocation
	{
	public:
		AdapterConnection( boost::asio::io_service & _service, const ConnectionCachePtr & _connectionCache, std::size_t _endpointId );

	public:
		ArchiveWrite & beginMessage( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response ) override;		

	public:
		void dispatchMessage( ArchiveRead & _read, std::size_t _size ) override;
		
		void connectionSuccessful( ArchiveRead & _ar, std::size_t _size ) override;
		void connectionFailed( ArchiveRead & _ar, std::size_t _size ) override;

	protected:
		std::size_t addDispatch( const ResponsePtr & _response );
		void writeBody( ArchiveWrite & _archive, std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response );

	protected:
		typedef std::map<std::size_t, ResponsePtr> TMapResponse;
		TMapResponse m_dispatch;

		std::size_t m_messageEnum;

		ConnectionCachePtr m_connectionCache;
	};

	typedef AxeHandle<AdapterConnection> AdapterConnectionPtr;
}