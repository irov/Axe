#	pragma once

#	include "session.hpp"

class response_base;

class stream_write;
class stream_read;

class connection
{
public:
	virtual stream_write * begin_message( std::size_t _servantId, std::size_t _methodId, response_base * _response ) = 0;

public:
	virtual void procces() = 0;
};