#	pragma once

#	include <AxeUtil/ArchiveRead.hpp>

#	include <Axe/ConnectionCache.hpp>

namespace Axe
{
	class ArchiveDispatcher
		: public AxeUtil::ArchiveRead
	{
	public:
		ArchiveDispatcher( ArchiveDispatcher & _archiveDispatcher );
		ArchiveDispatcher( const ConnectionCachePtr & _connectionCache );
		ArchiveDispatcher( AxeUtil::Archive & _archive, const ConnectionCachePtr & _connectionCache );
	
	public:
		const ConnectionCachePtr & getConnectionCache() const;

	protected:
		ConnectionCachePtr m_connectionCache;
	};
}