#	include "pch.hpp"

#	include "../SLAxe/SLAxe.hpp"

void main()
{
	Axe::SLAxe slaxe;

	const char * protocol = "grid.hpp";
	const char * path = "../Protocols/";

	bool done = slaxe.generate( protocol, path, "grid" );

	if( done == false )
	{
		printf("generate false\n");
	}
}