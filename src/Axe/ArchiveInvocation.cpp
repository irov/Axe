#	include "pch.hpp"

#	include "ArchiveInvocation.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	ArchiveInvocation::ArchiveInvocation( const ConnectionCachePtr & _connectionCache )
		: m_connectionCache(_connectionCache)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	const ConnectionCachePtr & ArchiveInvocation::getConnectionCache() const
	{
		return m_connectionCache;
	}
}