#	pragma once

#	include <AxeUtil/Shared.hpp>

namespace Axe
{
	class ArchiveInvocation;

	typedef AxeHandle<class Response> ResponsePtr;

	class Connection
		: virtual public AxeUtil::Shared
	{
	public:
		Connection( std::size_t _adapterId );

	public:
		virtual ArchiveInvocation & beginMessage( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response ) = 0;

		virtual void processMessage() = 0;

	public:
		std::size_t getAdapterId() const;

	protected:
		std::size_t m_adapterId;
	};

	typedef AxeHandle<Connection> ConnectionPtr;
}