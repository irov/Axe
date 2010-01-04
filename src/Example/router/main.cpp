#	pragma once

#	include <Axe/pch.hpp>
#	include <Axe/Communicator.hpp>
#	include <Axe/Router.hpp>

#	include <stdio.h>

class MyRouterCreateResponse
	: public Axe::RouterCreateResponse
{
public:
	void onCreate( const Axe::RouterPtr & _router ) override
	{
		_router->start();
	}

	void onFailed() override
	{

	}
};

class MyCommunicatorInitializeResponse
	: public Axe::CommunicatorConnectResponse
{
public:
	void onConnect( const Axe::CommunicatorPtr & _communicator ) override
	{
		boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"), 12000);

		_communicator->createRouter( ep, "Router", new MyRouterCreateResponse() );
	}

	void onFailed() override
	{

	}
};

void main()
{
	Axe::CommunicatorPtr cm = new Axe::Communicator();

	boost::asio::ip::tcp::endpoint grid_ep(boost::asio::ip::address::from_string("127.0.0.1"), 12001);
	
	cm->initialize( grid_ep, new MyCommunicatorInitializeResponse() );

	cm->run();
}