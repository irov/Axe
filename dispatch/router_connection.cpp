#	include "pch.hpp"

#	include "router_connection.hpp"

#	include "response_base.hpp"

#	include "stream.hpp"

router_proxy_connection::router_proxy_connection( router_connection * _base, std::size_t _id )
	: m_base(_base)
	, m_id(_id)
{

}

stream_write * router_proxy_connection::begin_message( std::size_t _servantId, std::size_t _methodId, response_base * _response )
{
	stream_write * stream 
		= m_base->begin_message( _servantId, _methodId, _response );

	stream->write( m_id );

	return stream;
}

void router_proxy_connection::procces()
{
	m_base->procces();
}

router_connection::router_connection( boost::asio::io_service & _service )
: adapter_connection( _service )
{

}

void router_connection::dispatch_message( std::size_t _size )
{
	std::size_t responseId;
	m_streamIn->read( responseId );

	TMapResponse::iterator it_found = m_dispatch.find( responseId );

	response_base * response = it_found->second;

	response->response_call( m_streamIn );

	m_streamIn->clear();
}

connection * router_connection::get_connection( std::size_t _id )
{
	TMapRouterConnections::iterator it_found = m_connections.find( _id );

	if( it_found == m_connections.end() )
	{
		router_proxy_connection * cn = new router_proxy_connection( this, _id );

		it_found = m_connections.insert( std::make_pair( _id, cn ) ).first;
	}

	return it_found->second;
}
