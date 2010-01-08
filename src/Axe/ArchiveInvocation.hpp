#	pragma once

#	include <AxeUtil/ArchiveWrite.hpp>

#	include <Axe/ConnectionCache.hpp>

namespace Axe
{
	class ArchiveInvocation
		: public AxeUtil::ArchiveWrite
	{
	public:
		ArchiveInvocation( const ConnectionCachePtr & _connectionCache );
	public:
		const ConnectionCachePtr & getConnectionCache() const;

	protected:
		ConnectionCachePtr m_connectionCache;
	};
}