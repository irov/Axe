#	include "pch.hpp"

#	include <Axe/RouterSession.hpp>

#	include <Axe/ArchiveInvocation.hpp>
#	include <Axe/ArchiveDispatcher.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	RouterSession::RouterSession( boost::asio::io_service & _service, const RouterPtr & _router, const ConnectionCachePtr & _connectionCache )
		: Session(_service, _connectionCache)
		, m_router(_router)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void RouterSession::dispatchMessage( ArchiveDispatcher & _ar, std::size_t _size )
	{
		m_router->dispatchMethod( _ar, _size, this );
	}
	//////////////////////////////////////////////////////////////////////////
	void RouterSession::permissionVerify( ArchiveDispatcher & _ar, std::size_t _size )
	{
		std::string login;
		std::string password;

		_ar.readString( login );
		_ar.readString( password );

		m_router->permissionVerify( login, password, this );
	}
}