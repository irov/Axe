#	pragma once

#	include "../Axe/Reception.hpp"

void main()
{
	Axe::ReceptionPtr rc = new Axe::Reception;

	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"), 12000);

	rc->connect( "login", "password", ep, new MyClient );

	rc->run();
}