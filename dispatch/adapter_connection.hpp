#	pragma once

#	include "session_connection.hpp"

class adapter_connection
	: public session_connection
{
public:
	adapter_connection( boost::asio::io_service & _service );

public:
	stream_write * begin_message( std::size_t _servantId, std::size_t _methodId, response_base * _response ) override;

public:
	void dispatch_message( std::size_t _size ) override;

protected:
	std::size_t add_dispatch( response_base * _response );
	void write_body( std::size_t _servantId, std::size_t _methodId, response_base * _response );

protected:
	typedef std::map<std::size_t, response_base *> TMapResponse;
	TMapResponse m_dispatch;

	std::size_t m_messageEnum;
};