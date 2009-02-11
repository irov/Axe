#	pragma once

#	include "../Axe/pch.hpp"
#	include "../Axe/Router.hpp"

#	include <stdio.h>

void main()
{
	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"), 12000);

	Axe::RouterPtr router = new Axe::Router( ep );

	boost::asio::ip::tcp::endpoint grid_ep(boost::asio::ip::address::from_string("127.0.0.1"), 12001);

	router->initialize( grid_ep );
	router->run();
}