#	pragma once

#	include <AxeUtil/Shared.hpp>

#	include "ClusterCoord.hpp"

#	include <map>

namespace AxeLib
{
	typedef AxeHandle<class Cluster> ClusterPtr;

	class ClustersProvider
		: virtual public AxeUtil::Shared
	{
	public:
		void addCluster( int _row, int _column, const ClusterPtr & _cluster );
		const ClusterPtr & getCluster( int _row, int _column );

	protected:
		virtual ClusterPtr onCreateCluster( int _row, int _column );

	protected:
		typedef std::map<ClusterCoord, ClusterPtr, ClusterCoordLess> TMapClustersCache;
		TMapClustersCache m_clusters;
	};

	typedef AxeHandle<ClustersProvider> ClustersProviderPtr;

}