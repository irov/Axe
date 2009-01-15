#	include "pch.hpp"

#	include "router_session.hpp"

#	include "router.hpp"

#	include "session.hpp"
#	include "stream.hpp"

router_session::router_session( boost::asio::io_service & _service, router * _rt )
: session( _service )
, m_router(_rt)
{
}

stream_write * router_session::begin_response( std::size_t _responseId )
{
	m_streamWrite->begin();
	m_streamWrite->write( _responseId );

	return m_streamWrite;
}

void router_session::dispatch_message( std::size_t _size )
{
	std::size_t servantId;
	std::size_t methodId;
	std::size_t requestId;
	std::size_t endpointId;

	m_streamIn->read( servantId);
	m_streamIn->read( methodId);
	m_streamIn->read( requestId);
	m_streamIn->read( endpointId );

	std::size_t size_args = _size - sizeof(servantId) - sizeof(methodId) - sizeof(requestId) - sizeof(endpointId);

	m_router->dispatch_method( size_args, servantId, methodId, requestId, endpointId, this );
}