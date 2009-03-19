#	pragma once

#	include <Axe/Shared.hpp>

namespace Axe
{
	typedef AxeHandle<class Proxy_Player> Proxy_PlayerPtr;

	class ClientConnectResponse
		: virtual public Shared
	{
	public:
		virtual void connectSuccessful( const Proxy_PlayerPtr & _player ) = 0;
		virtual void connectFailed() = 0;
	};

	typedef AxeHandle<ClientConnectResponse> ClientConnectResponsePtr;
}