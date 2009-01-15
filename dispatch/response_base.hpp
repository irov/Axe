#	pragma once

class stream_read;

class response_base
{
public:
	virtual void response_call( stream_read * _cn ) = 0;
};