#	pragma once

#	include "Shared.hpp"

namespace Axe
{
	typedef AxeHandle<class AdapterSession> AdapterSessionPtr;

	class Servant
		:	public Shared
	{
	public:
		virtual void call_method( std::size_t _id, std::size_t _requestId, const AdapterSessionPtr & _session ) = 0;
	};
}