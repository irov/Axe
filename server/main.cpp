#	include "pch.hpp"

#	include "dispatch/communicator.hpp"
#	include "dispatch/adapter.hpp"

#	include "protocols/protocol_grid.hpp"

class grid
	: public protocol_grid::servant
{
public:
	void add_adapter ( protocol_grid::bellhop_add_adapter * _bellhop, std::string a0, std::string a1, unsigned short a2 ) override
	{
		printf("a0 - %s\n", a0.c_str() );
		printf("a1 - %s\n", a1.c_str() );
		printf("a2 - %d\n", a2 );
		_bellhop->response( 32 );
	}

	void get_adapter_name ( protocol_grid::bellhop_get_adapter_name * _bellhop, std::string a0 ) override
	{

	}

	void get_adapter_id ( protocol_grid::bellhop_get_adapter_id * _bellhop, size_t a0 ) override
	{

	}
};

void main()
{
	communicator * cm = new communicator;

	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"), 12000);

	adapter * ap = cm->add_adapter( 0, ep );

	ap->add_servant( new grid );

	ap->initialize();

	cm->run();
}