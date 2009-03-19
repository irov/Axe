#	pragma once

#	include <Axe/Shared.hpp>

#	include <Axe/AdapterSession.hpp>

namespace Axe
{
	//typedef AxeHandle<class AdapterSession> AdapterSessionPtr;

	class Bellhop
		: virtual public Shared
	{
	public:
		Bellhop( std::size_t _requestId, const SessionPtr & _session );

	protected:
		std::size_t m_requestId;
		SessionPtr m_session;
	};

	typedef AxeHandle<Bellhop> BellhopPtr;	
}