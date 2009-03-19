#	pragma once

#	include <Axe/Shared.hpp>

namespace Axe
{
	typedef AxeHandle<class Proxy_GridManager> Proxy_GridManagerPtr;

	class GridConnectResponse
		: virtual public Shared
	{
	public:
		virtual void connectSuccessful( const Proxy_GridManagerPtr & _gridManager ) = 0;
		virtual void connectFailed() = 0;
	};

	typedef AxeHandle<GridConnectResponse> GridConnectResponsePtr;
}