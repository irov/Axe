#	pragma once

#	include "Response.hpp"
#	include "RouterSession.hpp"

namespace Axe
{
	class RouterResponse
		: public Response
	{
	public:
		RouterResponse( std::size_t _requestId, const RouterSessionPtr & _session );

	public:
		void responseCall( ArchiveRead & _ar ) override;

	protected:
		std::size_t m_requestId;
		RouterSessionPtr m_session;
	};
}