#	include "pch.hpp"
#	include <Axe/ArchiveDispatcher.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	ArchiveDispatcher::ArchiveDispatcher( ArchiveDispatcher & _archiveDispatcher )
		: AxeUtil::ArchiveRead(_archiveDispatcher.m_archive)
		, m_connectionCache(_archiveDispatcher.m_connectionCache)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveDispatcher::ArchiveDispatcher( const ConnectionCachePtr & _connectionCache )
		: m_connectionCache(_connectionCache)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveDispatcher::ArchiveDispatcher( AxeUtil::Archive & _archive, const ConnectionCachePtr & _connectionCache )
		: AxeUtil::ArchiveRead(_archive)
		, m_connectionCache(_connectionCache)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	const ConnectionCachePtr & ArchiveDispatcher::getConnectionCache() const
	{
		return m_connectionCache;
	}
}