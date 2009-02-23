#	include "pch.hpp"

#	include "../SLAxe/SLAxe.hpp"

void main()
{
	{
		Axe::SLAxe slaxe;

		const char * protocol = "Player.hpp";
		const char * path = "../AxeProtocols/";

		bool done = slaxe.generate( protocol, path, "Player" );

		if( done == false )
		{
			printf("generate false\n");
		}
	}
}