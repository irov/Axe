#	pragma once

#	include "Shared.hpp"

#	include "AdapterSession.hpp"

namespace Axe
{
	//typedef AxeHandle<class AdapterSession> AdapterSessionPtr;

	class Bellhop
		: virtual public Shared
	{
	public:
		Bellhop( std::size_t _requestId, const AdapterSessionPtr & _session );

	protected:
		std::size_t m_requestId;
		AdapterSessionPtr m_session;
	};

	typedef AxeHandle<Bellhop> BellhopPtr;	
}