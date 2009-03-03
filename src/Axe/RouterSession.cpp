#	include "pch.hpp"

#	include "RouterSession.hpp"

#	include "ArchiveWrite.hpp"
#	include "ArchiveRead.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	RouterSession::RouterSession( boost::asio::io_service & _service, const RouterPtr & _router, const ConnectionCachePtr & _connectionCache )
		: Session(_service, _connectionCache)
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
		std::size_t hostId;

		_ar.read( servantId);
		_ar.readSize( methodId);
		_ar.readSize( requestId);
		_ar.readSize( hostId );

		std::size_t size_args = _size - sizeof(servantId) - sizeof(methodId) - sizeof(requestId) - sizeof(hostId);

		m_router->dispatchMethod( size_args, servantId, methodId, requestId, hostId, this );
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