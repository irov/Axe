#	include "pch.hpp"

#	include "Bellhop.hpp"

namespace Axe
{
	Bellhop::Bellhop( std::size_t _requestId, const SessionPtr & _session )
		: m_requestId(_requestId)
		, m_session(_session)
	{
	}
}