#	pragma once

#	include "../Axe/pch.hpp"
#	include "../Axe/Client.hpp"
#	include "../Axe/Client.hpp"
#	include "../AxeProtocols/Player.hpp"

#	include <stdio.h>

class MyClientResponse_Player_test
	: public Axe::Response_Player_test
{
protected:
	void response( int _id ) override
	{
		printf( "Response_Player_test %d"
			, _id
			);
	}

	void throw_exception( const Axe::Exception & _ex ) override
	{
		printf( "Response_Player_test throw_exception" );	
	};
};

class MyClient
	:	public Axe::ClientConnectResponse
{
protected:
	void connectSuccessful( const Axe::Proxy_PlayerPtr & _player ) override
	{
		printf("connectSuccessful\n");

		Axe::PlayerInfo pi;

		pi.id = 2;
		pi.name = "test";

		_player->test( pi, new MyClientResponse_Player_test );
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