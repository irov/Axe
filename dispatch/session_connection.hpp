#	pragma once

#	include "connection.hpp"
#	include "session.hpp"

class session_connection
	: public connection
	, public session
{
public:
	session_connection( boost::asio::io_service & _service );

public:
	void procces() override;
};