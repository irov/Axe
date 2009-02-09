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
		ArchiveWrite & ar = Session::beginResponse();
		
		ar.writeSize( _responseId );

		return ar;
	}
	//////////////////////////////////////////////////////////////////////////
	void RouterSession::dispatchMessage( ArchiveRead & _ar, std::size_t _size )
	{
		std::size_t servantId;
		std::size_t methodId;
		std::size_t requestId;
		std::size_t endpointId;

		_ar.read( servantId);
		_ar.readSize( methodId);
		_ar.readSize( requestId);
		_ar.readSize( endpointId );

		std::size_t size_args = _size - sizeof(servantId) - sizeof(methodId) - sizeof(requestId) - sizeof(endpointId);

		m_router->dispatchMethod( size_args, servantId, methodId, requestId, endpointId, this );
	}
	//////////////////////////////////////////////////////////////////////////
	void RouterSession::permissionVerify( ArchiveRead & _ar, std::size_t _size )
	{
		std::string login;
		std::string password;

		_ar.readString( login );
		_ar.readString( password );

		m_router->permissionVerify( login, password, this );
	}
}