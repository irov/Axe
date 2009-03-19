#	pragma once

#	include <Axe/Session.hpp>
#	include <Axe/Router.hpp>

namespace Axe
{
	class RouterSession
		: public Session
	{
	public:
		RouterSession( boost::asio::io_service & _service, const RouterPtr & _rt, const ConnectionCachePtr & _connectionCache );

	public:
		void dispatchMessage( ArchiveRead & _ar, std::size_t _size ) override;
		void permissionVerify( ArchiveRead & _ar, std::size_t _size ) override;

	protected:
		RouterPtr m_router;
	};

	typedef AxeHandle<RouterSession> RouterSessionPtr;
}