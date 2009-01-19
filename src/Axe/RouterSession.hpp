#	pragma once

#	include "session.hpp"

namespace Axe
{
	typedef AxeHandle<class Router> RouterPtr;

	class RouterSession
		: public Session
	{
	public:
		RouterSession( boost::asio::io_service & _service, const RouterPtr & _rt );

	public:
		ArchiveWrite & beginResponse( std::size_t _responseId );

	public:
		void dispatchMessage( std::size_t _size ) override;

	protected:
		RouterPtr m_router;
	};
}