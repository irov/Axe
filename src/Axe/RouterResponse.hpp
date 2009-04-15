#	pragma once

#	include <Axe/Response.hpp>
#	include <Axe/RouterSession.hpp>

namespace Axe
{
	class RouterResponse
		: public Response
	{
	public:
		RouterResponse( std::size_t _requestId, const RouterSessionPtr & _session );

	public:
		void responseCall( ArchiveDispatcher & _ar, std::size_t _size ) override;
		void exceptionCall( ArchiveDispatcher & _ar, std::size_t _size ) override;

	protected:
		void throw_exception( const Exception & _ex ) override;

	protected:
		std::size_t m_requestId;
		RouterSessionPtr m_session;
	};
}