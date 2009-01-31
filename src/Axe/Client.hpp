#	pragma once

#	include "Shared.hpp"

namespace Axe
{
	typedef AxeHandle<class Proxy_Player> Proxy_PlayerPtr;

	class ClientResponse
		: public Shared
	{
	public:
		virtual void onConnect( const Proxy_PlayerPtr & _player ) = 0;
	};

	typedef AxeHandle<Client> ClientPtr;

}
