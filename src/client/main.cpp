#	pragma once

#	include "../Axe/pch.hpp"
#	include "../Axe/Client.hpp"
#	include "../Axe/Client.hpp"
#	include "../AxeProtocols/Player.hpp"

#	include <stdio.h>

class MyClient
	:	public Axe::ClientConnectResponse
{
protected:
	void connectSuccessful( const Axe::Proxy_PlayerPtr & _player ) override
	{
		printf("connectSuccessful");
	}

	void connectFailed() override
	{
		printf("connectFailed");
	}
};

void main()
{
	Axe::ClientPtr rc = new Axe::Client;

	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"), 12000);

	rc->connect( ep, "test", "test", new MyClient );

	rc->run();
}