#	include "pch.hpp"

#	include <Axe/RouterResponse.hpp>

#	include <Axe/Session.hpp>

#	include <Axe/ArchiveDispatcher.hpp>
#	include <Axe/ArchiveInvocation.hpp>

namespace Axe
{
	RouterResponse::RouterResponse( std::size_t _requestId, const SessionPtr & _session )
		: m_requestId(_requestId)
		, m_session(_session)
	{

	}
	//////////////////////////////////////////////////////////////////////////
	void RouterResponse::responseCall( ArchiveDispatcher & _ar, std::size_t _size )
	{
		std::size_t lenght = _ar.length( _size );
		const AxeUtil::Archive::value_type * args_buff = _ar.selectBuffer( lenght );

		ArchiveInvocation & write = m_session->beginResponse( m_requestId );
		write.writeArchive( args_buff, lenght );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void RouterResponse::exceptionCall( std::size_t _exceptionId, ArchiveDispatcher & _ar, std::size_t _size )
	{
		std::size_t lenght = _ar.length( _size );
		const AxeUtil::Archive::value_type * args_buff = _ar.selectBuffer( lenght );

		ArchiveInvocation & write = m_session->beginException( m_requestId );
		write.writeArchive( args_buff, lenght );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void RouterResponse::throw_exception( const Exception & _ex )
	{
		//Empty
	}
}