#	pragma once

#	include "session.hpp"

namespace Axe
{
	class ArchiveWrite;

	typedef AxeHandle<class Response> ResponsePtr;

	class Connection
		:	public Shared
	{
	public:
		virtual ArchiveWrite & beginMessage( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response ) = 0;

	public:
		virtual void procces() = 0;
	};
}