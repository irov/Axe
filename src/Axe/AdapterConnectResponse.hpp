#	pragma once

#	include "Shared.hpp"

namespace Axe
{
	typedef AxeHandle<class Proxy_Player> Proxy_PlayerPtr;

	class AdapterConnectResponse
		: virtual public Shared
	{
	public:
		virtual void connectSuccessful( std::size_t _enumeratorID ) = 0;
		virtual void connectFailed() = 0;
	};

	typedef AxeHandle<AdapterConnectResponse> AdapterConnectResponsePtr;
}