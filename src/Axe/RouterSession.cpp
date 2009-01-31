#	include "pch.hpp"

#	include "RouterSession.hpp"

#	include "ArchiveWrite.hpp"
#	include "ArchiveRead.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	RouterSession::RouterSession( boost::asio::io_service & _service, const RouterPtr & _router )
		: Session(_service)
		, m_router(_router)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveWrite & RouterSession::beginResponse( std::size_t _responseId )
	{
		ArchiveWrite & ar = this->beginResponse();
		
		ar.writeSize( _responseId );

		return ar;
	}
	//////////////////////////////////////////////////////////////////////////
	void RouterSession::dispatchMessage( std::size_t _size )
	{
		std::size_t servantId;
		std::size_t methodId;
		std::size_t requestId;
		std::size_t endpointId;

		m_streamIn->read( servantId);
		m_streamIn->readSize( methodId);
		m_streamIn->readSize( requestId);
		m_streamIn->readSize( endpointId );

		std::size_t size_args = _size - sizeof(servantId) - sizeof(methodId) - sizeof(requestId) - sizeof(endpointId);

		m_router->dispatchMethod( size_args, servantId, methodId, requestId, endpointId, this );
	}
}