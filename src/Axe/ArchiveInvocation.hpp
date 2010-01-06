#	pragma once

#	include <AxeUtil/ArchiveWrite.hpp>

#	include <Axe/ConnectionCache.hpp>

namespace Axe
{
	class ArchiveInvocation
		: public AxeUtil::ArchiveWrite
	{
	public:
		ArchiveInvocation( const ConnectionCachePtr & _connectionCache )
			: m_connectionCache(_connectionCache)
		{

		}

	public:
		const ConnectionCachePtr & getConnectionCache() const
		{
			return m_connectionCache;
		}

	protected:
		ConnectionCachePtr m_connectionCache;
	};
}