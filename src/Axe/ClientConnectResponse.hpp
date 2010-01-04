#	pragma once

#	include <AxeUtil/Shared.hpp>

namespace Axe
{
	typedef AxeHandle<class Proxy_Session> Proxy_SessionPtr;

	class ClientConnectResponse
		: virtual public AxeUtil::Shared
	{
	public:
		virtual void connectSuccessful( const Proxy_SessionPtr & _session ) = 0;
		virtual void connectFailed() = 0;
	};

	typedef AxeHandle<ClientConnectResponse> ClientConnectResponsePtr;
}