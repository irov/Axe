#	pragma once

#	include "session.hpp"

class adapter;

class adapter_session
	: public session
{
public:
	adapter_session( boost::asio::io_service & _service, adapter * _ad );

public:
	stream_write * begin_response( std::size_t _responseId );

public:
	void dispatch_message( std::size_t _size ) override;

protected:
	adapter * m_adapter;
};