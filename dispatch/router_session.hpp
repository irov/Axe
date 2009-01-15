#	pragma once

#	include "session.hpp"

class router;

class router_session
	: public session
{
public:
	router_session( boost::asio::io_service & _service, router * _rt );

public:
	stream_write * begin_response( std::size_t _responseId );

public:
	void dispatch_message( std::size_t _size ) override;

protected:
	router * m_router;
};