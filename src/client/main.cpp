#	pragma once

#	include "../Axe/pch.hpp"
#	include "../Axe/Client.hpp"
#	include "../Axe/Client.hpp"
#	include "../AxeProtocols/Player.hpp"

#	include <stdio.h>

class MyClient
	:	public Axe::Client
{
protected:
	void onConnect( const Axe::Proxy_PlayerPtr & _player ) override
	{
		printf("fdsfs");
	}
};

void main()
{
	Axe::ClientPtr rc = new Axe::Client;

	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"), 12000);

	rc->connect( ep, "login", "password", new MyClient );

	rc->run();
}