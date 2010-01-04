#	include "pch.hpp"

#	include <SLAxe/SLAxe.hpp>

void main()
{
	Axe::SLAxe slaxe;

	slaxe.generate( "EvictorManager.axe", "../AxeProtocols/", "EvictorManager" );
	slaxe.generate( "GridManager.axe", "../AxeProtocols/", "GridManager" );
	slaxe.generate( "PermissionsVerifier.axe", "../AxeProtocols/", "PermissionsVerifier" );
	slaxe.generate( "SessionManager.axe", "../AxeProtocols/", "SessionManager" );
	slaxe.generate( "Player.axe", "../AxeProtocols/", "Player" );
}