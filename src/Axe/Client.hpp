#	pragma once

#	include "Shared.hpp"

namespace Axe
{
	class Client
		: public Servant
	{
	public:
		virtual void onConnect( const Proxy_PlayerPtr & _player ) = 0;
	};

	typedef AxeHandle<Client> ClientPtr;

}
