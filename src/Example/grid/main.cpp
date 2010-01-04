#	pragma once

#	include "pch.hpp"
#	include <Axe/Communicator.hpp>

#	include <AxeLib/GridManager/GridManager.hpp>

#	include <stdio.h>

class MyGridCreateResponse
	: public Axe::GridCreateResponse
{
public:
	void onCreate( const Axe::GridPtr & _grid ) override
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
	
	AxeLib::GridManagerPtr grid = new AxeLib::GridManager;

	cm->createGrid( ep, "Grid", grid, new MyGridCreateResponse );

	cm->run();
}