#	include "pch.hpp"

#	include "../SLAxe/SLAxe.hpp"

void main()
{
	{
		Axe::SLAxe slaxe;

		const char * protocol = "Player.hpp";
		const char * path = "../AxeProtocols/";

		
		slaxe.generate( "EvictorManager.axe", "../AxeProtocols/", "EvictorManager" );
		slaxe.generate( "GridManager.axe", "../AxeProtocols/", "GridManager" );
		slaxe.generate( "PermissionsVerifier.axe", "../AxeProtocols/", "PermissionsVerifier" );
		slaxe.generate( "SessionManager.axe", "../AxeProtocols/", "SessionManager" );
		slaxe.generate( "Player.hpp", "../AxeProtocols/", "Player" );
	}
}