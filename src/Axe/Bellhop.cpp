#	include "pch.hpp"

#	include "Bellhop.hpp"

namespace Axe
{
	Bellhop::Bellhop( std::size_t _requestId, const AdapterSessionPtr & _session )
		: m_requestId(_requestId)
		, m_session(_session)
	{
	}
}