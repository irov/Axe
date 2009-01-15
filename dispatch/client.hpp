#	pragma once

class client
{
public:
	virtual void on_connect( std::size_t _id ) = 0;
};