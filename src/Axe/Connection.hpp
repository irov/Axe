#	pragma once

#	include "Shared.hpp"

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
		virtual void process() = 0;
	};

	typedef AxeHandle<Connection> ConnectionPtr;
}