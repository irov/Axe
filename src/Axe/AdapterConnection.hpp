#	pragma once

#	include "SessionConnection.hpp"

namespace Axe
{
	typedef AxeHandle<class Response> ResponsePtr;

	class AdapterConnection
		: public SessionConnection
	{
	public:
		AdapterConnection( boost::asio::io_service & _service );

	public:
		ArchiveWrite & beginMessage( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response ) override;

	public:
		void dispatchMessage( std::size_t _size ) override;

	protected:
		std::size_t addDispatch( const ResponsePtr & _response );
		void writeBody( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response );

	protected:
		typedef std::map<std::size_t, ResponsePtr> TMapResponse;
		TMapResponse m_dispatch;

		std::size_t m_messageEnum;
	};
}