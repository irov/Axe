#	pragma once

#	include <AxeUtil/Shared.hpp>

#	include "Cluster.hpp"
#	include "ClusterCoord.hpp"

namespace AxeLib
{
	typedef AxeHandle<class Cluster> ClusterPtr;
	typedef AxeHandle<class ClustersProvider> ClustersProviderPtr;

	class ClustersSpaceListener
		: virtual public AxeUtil::Shared
	{
	public:
		virtual void onClusterInsertAvatar( const ClusterPtr & _cluster, const ClusterElementPtr & _element, bool _master ) = 0;
		virtual void onClusterRemoveAvatar( const ClusterPtr & _cluster, const ClusterElementPtr & _element, bool _master ) = 0;

		virtual void onClusterMoveInsertAvatar( const ClusterPtr & _cluster, const ClusterElementPtr & _element, float _newX, float _newZ, bool _master ) = 0;
		virtual void onClusterMoveUpdateAvatar( const ClusterPtr & _cluster, const ClusterElementPtr & _element, float _newX, float _newZ, bool _master, bool _oldmaster ) = 0;
		virtual void onClusterMoveRemoveAvatar( const ClusterPtr & _cluster, const ClusterElementPtr & _element, bool _master ) = 0;
	};

	typedef AxeHandle<ClustersSpaceListener> ClustersSpaceListenerPtr;

	class ClustersSpace
		: virtual public AxeUtil::Shared
	{
	public:
		ClustersSpace( float _clusterSize, const ClustersProviderPtr & _clusterCache, const ClustersSpaceListenerPtr & _listener );

	public:
		void insertElement( const ClusterElementPtr & _element, float _x, float _z );
		void removeElement( const ClusterElementPtr & _element, float _x, float _z );
		void moveElement( const ClusterElementPtr & _element, float _fromX, float _fromZ, float _toX, float _toZ );

	public:
		void addCluster( int _row, int _column, const ClusterPtr & _cluster );
		const ClusterPtr & getCluster( int _row, int _column );

	protected:
		int posToColumn( float _x ) const;
		int posToRow( float _z ) const;

		void makeViewport( ClusterViewport & _viewport, float _x, float _z, float _radius ) const;

	protected:
		float m_clusterSize;

		ClustersProviderPtr m_cache;
		ClustersSpaceListenerPtr m_listener;
	};
	//////////////////////////////////////////////////////////////////////////
	typedef AxeHandle<ClustersSpace> ClustersSpacePtr;
}
