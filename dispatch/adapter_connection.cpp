#	include "pch.hpp"

#	include "adapter_connection.hpp"

#	include "communicator.hpp"
#	include "session.hpp"
#	include "stream.hpp"
#	include "adapter.hpp"
#	include "response_base.hpp"

adapter_connection::adapter_connection( boost::asio::io_service & _service )
: session_connection( _service )
, m_messageEnum(0)
{
}

stream_write * adapter_connection::begin_message( std::size_t _servantId, std::size_t _methodId, response_base * _response )
{
	m_streamWrite->begin();

	this->write_body( _servantId, _methodId, _response );

	return m_streamWrite;
}

std::size_t adapter_connection::add_dispatch( response_base * _response )
{
	++m_messageEnum;
	m_dispatch.insert( std::make_pair( m_messageEnum, _response ) );

	return m_messageEnum;
}

void adapter_connection::write_body( std::size_t _servantId, std::size_t _methodId, response_base * _response )
{
	std::size_t messageId = this->add_dispatch( _response );

	m_streamWrite->write( _servantId );
	m_streamWrite->write( _methodId );
	m_streamWrite->write( messageId );
}

void adapter_connection::dispatch_message( std::size_t _size )
{
	std::size_t responseId;
	m_streamIn->read( responseId );

	TMapResponse::iterator it_found = m_dispatch.find( responseId );

	response_base * response = it_found->second;

	response->response_call( m_streamIn );

	m_streamIn->clear();
}