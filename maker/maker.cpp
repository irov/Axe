#	include "pch.hpp"

#	include "protocol_declare.hpp"
#	include "protocol_implement.hpp"

#	include "maker.hpp"

void main()
{
	MAKE_PROTOCOL( test, 
		CARBON_METHOD_VOID( foo, (int)(float) )
		CARBON_METHOD( bar, (int), (float) )
		CARBON_METHOD( moo, (int)(float)(float), (float)(float) )
		CARBON_METHOD_VOID( too, (float) )
		);

	MAKE_PROTOCOL( grid, 
		CARBON_METHOD( add_adapter, (std::string)(std::string)(unsigned short), (std::size_t) )
		CARBON_METHOD( get_servant_info, (std::string), (std::string)(unsigned short) )
		CARBON_METHOD( get_adapter_id, (size_t), (std::string)(unsigned short) )
		);

	MAKE_PROTOCOL( session_manager, 
		CARBON_METHOD( create, (std::string)(std::string), (std::size_t) )
		);
}