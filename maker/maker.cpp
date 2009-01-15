#	include "pch.hpp"

//#	include "protocol_declare.hpp"
//#	include "protocol_implement.hpp"

//#	include "maker.hpp"

#	include "../SLAxe/SLAxe.hpp"

void main()
{
	//MAKE_PROTOCOL( test, 
	//	CARBON_METHOD_VOID( foo, (int)(float) )
	//	CARBON_METHOD( bar, (int), (float) )
	//	CARBON_METHOD( moo, (int)(float)(float), (float)(float) )
	//	CARBON_METHOD_VOID( too, (float) )
	//	);

	//MAKE_PROTOCOL( grid, 
	//	CARBON_METHOD( add_adapter, (std::string)(std::string)(unsigned short), (std::size_t) )
	//	CARBON_METHOD( get_servant_info, (std::string), (std::string)(unsigned short) )
	//	CARBON_METHOD( get_adapter_id, (size_t), (std::string)(unsigned short) )
	//	);

	//MAKE_PROTOCOL( session_manager, 
	//	CARBON_METHOD( create, (std::string)(std::string), (std::size_t) )
	//	);

	Axe::SLAxe slaxe;

	const char * protocol = "grid.hpp";
	const char * code = "../protocols/grid.hpp";

	slaxe.generate( protocol, code );
}