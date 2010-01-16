#	pragma once

#	include <Axe/Response.hpp>

namespace Axe
{
	typedef AxeHandle<class Session> SessionPtr;

	class RouterResponse
		: public Response
	{
	public:
		RouterResponse( std::size_t _requestId, const SessionPtr & _session );

	public:
		void responseCall( ArchiveDispatcher & _ar, std::size_t _size ) override;
		void exceptionCall( std::size_t _exceptionId, ArchiveDispatcher & _ar, std::size_t _size ) override;

	protected:
		void throw_exception( const Exception & _ex ) override;

	protected:
		std::size_t m_requestId;
		SessionPtr m_session;
	};
}