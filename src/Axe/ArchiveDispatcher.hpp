#	pragma once

#	include <AxeUtil/ArchiveRead.hpp>

#	include <Axe/ConnectionCache.hpp>

namespace Axe
{
	class ArchiveDispatcher
		: public AxeUtil::ArchiveRead
	{
	public:
		ArchiveDispatcher( const ConnectionCachePtr & _connectionCache );

	public:
		const ConnectionCachePtr & getConnectionCache() const;

	protected:
		ConnectionCachePtr m_connectionCache;
	};
}