#	pragma once

#	include "Connection.hpp"
#	include "Session.hpp"

namespace Axe
{
	class ArchiveRead;

	typedef AxeHandle<class Response> ResponsePtr;
	//typedef AxeHandle<class Session> SessionPtr;

	class AdapterConnection
		: public Connection
	{
	public:
		AdapterConnection( boost::asio::io_service & _service, std::size_t _endpointId );

	public:
		void connect( const boost::asio::ip::tcp::endpoint & _endpoint );

	public:
		ArchiveWrite & beginMessage( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response ) override;

	public:
		virtual void dispatchMessage( ArchiveRead & _read, std::size_t _size );

	protected:
		std::size_t addDispatch( const ResponsePtr & _response );
		void writeBody( ArchiveWrite & _archive, std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response );

	protected:
		SessionPtr m_session; 

		typedef std::map<std::size_t, ResponsePtr> TMapResponse;
		TMapResponse m_dispatch;

		std::size_t m_messageEnum;
	};
}