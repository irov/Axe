#	include "ClustersProvider.hpp"
#	include "Cluster.hpp"
#	include "ClusterElement.hpp"

namespace AxeLib
{
	//////////////////////////////////////////////////////////////////////////
	void ClustersProvider::addCluster( int _row, int _column, const ClusterPtr & _cluster )
	{
		ClusterCoord coord = { _row, _column };

		m_clusters.insert( std::make_pair( coord, _cluster ) );
	}
	//////////////////////////////////////////////////////////////////////////
	const ClusterPtr & ClustersProvider::getCluster( int _row, int _column )
	{
		ClusterCoord coord = { _row, _column };

		TMapClustersCache::iterator it_found = m_clusters.find( coord );

		if( it_found == m_clusters.end() )
		{
			ClusterPtr cluster = this->onCreateCluster( _row, _column );

			it_found = m_clusters.insert( std::make_pair( coord, cluster ) ).first;
		}

		return it_found->second;
	}
	//////////////////////////////////////////////////////////////////////////
	ClusterPtr ClustersProvider::onCreateCluster( int _row, int _column )
	{
		ClusterPtr cluster = new Cluster();

		return cluster;
	}
}