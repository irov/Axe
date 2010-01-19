#	include "pch.hpp"

#	include <Axe/Bellhop.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Bellhop::Bellhop( std::size_t _requestId, const SessionPtr & _session )
		: m_requestId(_requestId)
		, m_session(_session)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	Axe::ArchiveInvocation & Bellhop::beginResponse()
	{
		Axe::ArchiveInvocation & ar = m_session->beginResponse( m_requestId );
		return ar;
	}
	//////////////////////////////////////////////////////////////////////////
	Axe::ArchiveInvocation & Bellhop::beginException()
	{
		Axe::ArchiveInvocation & ar = m_session->beginException( m_requestId );
		return ar;
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop::process()
	{
		m_session->process();
	}
}