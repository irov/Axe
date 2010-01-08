#	include "pch.hpp"

#	include <SLAxe/SLAxe.hpp>

void main()
{
	Axe::SLAxe slaxe;

	slaxe.make( "EvictorManager.axe", "../AxeProtocols/", "EvictorManager" );
	slaxe.make( "GridManager.axe", "../AxeProtocols/", "GridManager" );
	slaxe.make( "PermissionsVerifier.axe", "../AxeProtocols/", "PermissionsVerifier" );
	slaxe.make( "SessionManager.axe", "../AxeProtocols/", "SessionManager" );
	slaxe.make( "Player.axe", "../AxeProtocols/", "Player" );
}