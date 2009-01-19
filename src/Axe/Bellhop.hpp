#	pragma once

#	include "Shared.hpp"

namespace Axe
{
	typedef AxeHandle<class AdapterSession> AdapterSessionPtr;

	class Bellhop
		: public Shared
	{
	public:
		Bellhop( std::size_t _requestId, const AdapterSessionPtr & _session );

	protected:
		std::size_t m_requestId;
		AdapterSessionPtr m_session;
	};
}