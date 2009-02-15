#	pragma once

#	include "../Axe/pch.hpp"
#	include "../Axe/Adapter.hpp"

#	include <stdio.h>

void main()
{
	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"), 12002);

	Axe::AdapterPtr adapter = new Axe::Adapter( ep, "Test" );

	boost::asio::ip::tcp::endpoint grid_ep(boost::asio::ip::address::from_string("127.0.0.1"), 12001);

	adapter->initialize( grid_ep );

	adapter->run();
}