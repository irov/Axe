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
	void RouterSession::dispatchMessage( ArchiveRead & _ar, std::size_t _size )
	{
		m_router->dispatchMethod( _ar, _size, this );
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