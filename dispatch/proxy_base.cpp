#	include "pch.hpp"
#	include "proxy_base.hpp"
#	include "communicator.hpp"

#	include "connection.hpp"

proxy_base::proxy_base( std::size_t _servantId, connection * _connection )
: m_servantId(_servantId)
, m_connection(_connection)
{
}

stream_write * proxy_base::begin_message( std::size_t _methodId, response_base * _response )
{
	stream_write * ssocket = m_connection->begin_message( m_servantId, _methodId, _response );

	return ssocket;
}

void proxy_base::procces()
{
	m_connection->procces();
}

std::size_t proxy_base::get_servantId() const
{
	return m_servantId;
}