#	pragma once

class response_base;
class stream_write;
class communicator;
class connection;

class proxy_base
{
public:
	proxy_base( std::size_t _servantId, connection * _connection );

public:
	stream_write * begin_message( std::size_t _methodId, response_base * _response );
	void procces();

public:
	std::size_t get_servantId() const;

protected:
	std::size_t m_servantId;
	connection * m_connection;
};