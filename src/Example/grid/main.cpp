#	pragma once

#	include <Axe/pch.hpp>
#	include <Axe/Grid.hpp>

#	include <stdio.h>

void main()
{
	boost::asio::ip::tcp::endpoint ep( boost::asio::ip::address::from_string("127.0.0.1"), 12001 );

	Axe::GridInitializerPtr gridInitialize = new Axe::GridInitializer();
	
	gridInitialize->run( ep, "Grid" );
}