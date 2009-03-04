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
	void RouterResponse::responseCall( ArchiveRead & _ar, std::size_t _size )
	{
		std::size_t lenght = _ar.length( _size );
		const Archive::value_type * args_buff = _ar.selectBuffer( lenght );

		ArchiveWrite & write = m_session->beginResponse( m_requestId );
		write.writeArchive( args_buff, lenght );
		m_session->process();
		//_cn->
	}
	//////////////////////////////////////////////////////////////////////////
	void RouterResponse::exceptionCall( ArchiveRead & _ar, std::size_t _size )
	{

	}
}