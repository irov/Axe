#	pragma once

#	include "Shared.hpp"

namespace Axe
{
	typedef AxeHandle<class AdapterSession> AdapterSessionPtr;
	typedef AxeHandle<class ConnectionCache> ConnectionCachePtr;
	
	class Servant
		:	public Shared
	{
	public:
		virtual void callMethod( std::size_t _id, std::size_t _requestId, const AdapterSessionPtr & _session, const ConnectionCachePtr & _connectionCache ) = 0;
	};
}