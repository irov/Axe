#	include "pch.hpp"

#	include "adapter_session.hpp"

#	include "adapter.hpp"

#	include "session.hpp"
#	include "stream.hpp"

adapter_session::adapter_session( boost::asio::io_service & _service, adapter * _ad )
: session( _service )
, m_adapter(_ad)
{
}

stream_write * adapter_session::begin_response( std::size_t _responseId )
{
	m_streamWrite->begin();
	m_streamWrite->write( _responseId );

	return m_streamWrite;
}

void adapter_session::dispatch_message( std::size_t _size )
{
	std::size_t servantId;
	std::size_t methodId;
	std::size_t requestId;

	m_streamIn->read( servantId);
	m_streamIn->read( methodId);
	m_streamIn->read( requestId);

	m_adapter->dispatch_method( servantId, methodId, requestId, this );
}