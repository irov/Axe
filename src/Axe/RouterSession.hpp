#	pragma once

#	include <Axe/Session.hpp>
#	include <Axe/Router.hpp>

namespace Axe
{
	class RouterSession
		: public Session
	{
	public:
		RouterSession( const SocketPtr & _socket, const RouterPtr & _rt, const ConnectionCachePtr & _connectionCache );

	public:
		void dispatchMessage( ArchiveDispatcher & _ar, std::size_t _size ) override;
		void permissionVerify( ArchiveDispatcher & _ar, std::size_t _size ) override;

	protected:
		RouterPtr m_router;
	};

	typedef AxeHandle<RouterSession> RouterSessionPtr;
}