#	pragma once

#	include "Shared.hpp"

namespace Axe
{
	class ArchiveRead;

	typedef AxeHandle<class ConnectionCache> ConnectionCachePtr;

	class Response
		: virtual public Shared
	{
	public:
		virtual void responseCall( ArchiveRead & _ar, const ConnectionCachePtr & _connectionCache ) = 0;
	};
}