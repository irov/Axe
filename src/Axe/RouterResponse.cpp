#	include "pch.hpp"

#	include "RouterResponse.hpp"
#	include "RouterSession.hpp"

#	include "ArchiveRead.hpp"

namespace Axe
{
	RouterResponse::RouterResponse( std::size_t _requestId, const RouterSessionPtr & _session )
		: m_requestId(_requestId)
		, m_session(_session)
	{

	}
	//////////////////////////////////////////////////////////////////////////
	void RouterResponse::responseCall( ArchiveRead & _ar )
	{
		//_cn->
	}
	//////////////////////////////////////////////////////////////////////////
	void RouterResponse::exceptionCall( ArchiveRead & _ar )
	{

	}
}