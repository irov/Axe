#	include "pch.hpp"
#	include <Axe/ArchiveDispatcher.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	ArchiveDispatcher::ArchiveDispatcher( const ConnectionCachePtr & _connectionCache )
		: m_connectionCache(_connectionCache)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	const ConnectionCachePtr & ArchiveDispatcher::getConnectionCache() const
	{
		return m_connectionCache;
	}
}