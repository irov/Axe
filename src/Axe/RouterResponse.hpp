#	pragma once

#	include "host.hpp"
#	include "response_base.hpp"

namespace Axe
{
	typedef AxeHandle<class RouterSession> RouterSessionPtr;

	class RouterResponse
		: public Response
	{
	public:
		RouterResponse( std::size_t _requestId, const RouterSessionPtr & _session );

	public:
		void responseCall( ArchiveRead & _ar ) override;

	protected:
		std::size_t m_requestId;
		router_session * m_session;
	};
}