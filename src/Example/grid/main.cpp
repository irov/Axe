#	pragma once

#	include <Axe/pch.hpp>
#	include <Axe/Communicator.hpp>

#	include <stdio.h>

class MyGridCreateResponse
	: public Axe::GridCreateResponse
{
public:
	void onCreate( const GridPtr & _grid ) override
	{

	}

	void onFailed() override
	{

	}
};

void main()
{
	boost::asio::ip::tcp::endpoint ep( boost::asio::ip::address::from_string("127.0.0.1"), 12001 );

	Axe::CommunicatorPtr cm = new Axe::Communicator();
	
	cm->initializeGrid( ep, "Grid", new MyCommunicatorInitializeResponse );
	cm->createGrid( ep, "Grid", new MyGridCreateResponse );

	cm->run();
}