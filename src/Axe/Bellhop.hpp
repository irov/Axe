#	pragma once

#	include <AxeUtil/Shared.hpp>

#	include <Axe/Session.hpp>

namespace Axe
{
	class Bellhop
		: virtual public AxeUtil::Shared
	{
	public:
		Bellhop( std::size_t _requestId, const SessionPtr & _session );

	public:
		Axe::ArchiveInvocation & beginResponse();
		Axe::ArchiveInvocation & beginException();
		void process();

	protected:
		std::size_t m_requestId;
		SessionPtr m_session;
	};

	typedef AxeHandle<Bellhop> BellhopPtr;	
}