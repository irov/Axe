#	pragma once

#	include "Session.hpp"
#	include "Router.hpp"

namespace Axe
{
	class RouterSession
		: public Session
	{
	public:
		RouterSession( boost::asio::io_service & _service, const RouterPtr & _rt );

	public:
		ArchiveWrite & beginResponse( std::size_t _responseId );

	public:
		void dispatchMessage( ArchiveRead & _ar, std::size_t _size ) override;
		void permissionVerify( ArchiveRead & _ar, std::size_t _size ) override;

	protected:
		RouterPtr m_router;
	};

	typedef AxeHandle<RouterSession> RouterSessionPtr;
}