#	include "pch.hpp"

#	include "protocols/protocol_grid.hpp"

#	include "dispatch/communicator.hpp"
#	include "dispatch/adapter.hpp"
#	include "dispatch/client.hpp"
#	include "dispatch/reception.hpp"

class MyResponse
	: public protocol_grid::response_add_adapter
{
public:
	void response( std::size_t _id ) override
	{
		printf("MyBarVisitor - %d\n", _id );
	}
};

class MyClient
	: public client
{
public:
	void on_connect( std::size_t _id ) override
	{
		
	}
};

void main()
{
	reception * rc = new reception;

	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"), 12000);

	rc->connect( "login", "password", ep, new MyClient );

	rc->run();
}