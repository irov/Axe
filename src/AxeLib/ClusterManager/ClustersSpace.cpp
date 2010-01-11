#	include "ClustersSpace.hpp"
#	include "ClustersProvider.hpp"
#	include "ClusterElement.hpp"


namespace AxeLib
{
	//////////////////////////////////////////////////////////////////////////
	ClustersSpace::ClustersSpace( float _clusterSize, const ClustersProviderPtr & _cache, const ClustersSpaceListenerPtr & _listener )
		: m_clusterSize(_clusterSize)
		, m_cache(_cache)
		, m_listener(_listener)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void ClustersSpace::insertElement( const ClusterElementPtr & _element, float _x, float _z )
	{
		float viewRadius = _element->getElementRadius();

		ClusterViewport vp;

		this->makeViewport( vp, _x, _z, viewRadius );

		int column_middle = this->posToColumn( _x );
		int row_middle = this->posToRow( _z );

		for( int 
			it_row = vp.br,
			it_row_end = vp.er;
		it_row != it_row_end;
		++it_row )
		{
			for( int 
				it_column = vp.bc,
				it_column_end = vp.ec;
			it_column != it_column_end;
			++it_column )
			{
				const ClusterPtr & cluster = m_cache->getCluster( it_row, it_column );

				bool master = ( it_row == row_middle && it_column == column_middle );

				m_listener->onClusterInsertAvatar( cluster, _element, master );

				cluster->insertElement( _element, master );
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void ClustersSpace::removeElement( const ClusterElementPtr & _element, float _x, float _z )
	{
		float viewRadius = _element->getElementRadius();

		ClusterViewport vp;

		this->makeViewport( vp, _x, _z, viewRadius );

		int column_middle = this->posToColumn( _x );
		int row_middle = this->posToRow( _z );

		for( int 
			it_row = vp.br,
			it_row_end = vp.er;
		it_row != it_row_end;
		++it_row )
		{
			for( int 
				it_column = vp.bc,
				it_column_end = vp.ec;
			it_column != it_column_end;
			++it_column )
			{
				const ClusterPtr & cluster = m_cache->getCluster( it_row, it_column );

				bool master = cluster->removeElement( _element );

				m_listener->onClusterRemoveAvatar( cluster, _element, master );
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void ClustersSpace::moveElement( const ClusterElementPtr & _element, float _fromX, float _fromZ, float _toX, float _toZ )
	{
		float viewRadius = _element->getElementRadius();

		ClusterViewport old_vp;
		this->makeViewport( old_vp, _fromX, _fromZ, viewRadius );

		ClusterViewport new_vp;
		this->makeViewport( new_vp, _toX, _toZ, viewRadius );

		int column_middle = this->posToColumn( _toX );
		int row_middle = this->posToRow( _toZ );

		for( int 
			it_row = new_vp.br,
			it_row_end = new_vp.er;
		it_row != it_row_end;
		++it_row )
		{
			for( int 
				it_column = new_vp.bc,
				it_column_end = new_vp.ec;
			it_column != it_column_end;
			++it_column )
			{
				if( testPoint( new_vp, it_row, it_column ) == false ) continue;
				if( testPoint( old_vp, it_row, it_column ) == true ) continue;

				const ClusterPtr & cluster = m_cache->getCluster( it_row, it_column );

				bool master = ( it_row == row_middle && it_column == column_middle );

				m_listener->onClusterMoveInsertAvatar( cluster, _element, _toX, _toZ, master );

				cluster->insertElement( _element, master );
			}
		}

		int old_column_middle = this->posToColumn( _fromX );
		int old_row_middle = this->posToRow( _fromZ );

		bool cluster_migrate = ( old_column_middle != column_middle || old_row_middle != row_middle );

		for( int 
			it_row = old_vp.br,
			it_row_end = old_vp.er;
		it_row != it_row_end;
		++it_row )
		{
			for( int 
				it_column = old_vp.bc,
				it_column_end = old_vp.ec;
			it_column != it_column_end;
			++it_column )
			{
				if( testPoint( new_vp, it_row, it_column ) == false ) continue;
				if( testPoint( old_vp, it_row, it_column ) == false ) continue;

				const ClusterPtr & cluster = m_cache->getCluster( it_row, it_column );

				bool master = ( it_row == row_middle && it_column == column_middle );
				bool old_master = ( it_row == old_row_middle && it_column == old_column_middle );

				if( cluster_migrate )
				{
					if( old_master == true )
					{
						cluster->changeElementMaster( _element, false );
					}
					else if( master == true )
					{
						cluster->changeElementMaster( _element, true );
					}
				}

				m_listener->onClusterMoveUpdateAvatar( cluster, _element, _toX, _toZ, master, old_master );
			}
		}

		for( int 
			it_row = old_vp.br,
			it_row_end = old_vp.er;
		it_row != it_row_end;
		++it_row )
		{
			for( int 
				it_column = old_vp.bc,
				it_column_end = old_vp.ec;
			it_column != it_column_end;
			++it_column )
			{
				if( testPoint( new_vp, it_row, it_column ) == true ) continue;
				if( testPoint( old_vp, it_row, it_column ) == false ) continue;

				const ClusterPtr & cluster = m_cache->getCluster( it_row, it_column );

				bool master = cluster->removeElement( _element );

				m_listener->onClusterMoveRemoveAvatar( cluster, _element, master );			
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void ClustersSpace::addCluster( int _row, int _column, const ClusterPtr & _cluster )
	{
		m_cache->addCluster( _row, _column, _cluster );
	}
	//////////////////////////////////////////////////////////////////////////
	const ClusterPtr & ClustersSpace::getCluster( int _row, int _column )
	{
		const ClusterPtr & cluster = m_cache->getCluster( _row, _column );

		return cluster;
	}
	//////////////////////////////////////////////////////////////////////////
	int ClustersSpace::posToColumn( float _x ) const
	{
		return floori( _x / m_clusterSize );
	}
	//////////////////////////////////////////////////////////////////////////
	int ClustersSpace::posToRow( float _z ) const
	{
		return floori( _z / m_clusterSize);
	}
	//////////////////////////////////////////////////////////////////////////
	void ClustersSpace::makeViewport( ClusterViewport & _viewport, float _x, float _z, float _radius ) const
	{
		_viewport.bc = posToColumn( _x - _radius );
		_viewport.br = posToRow( _z - _radius );

		_viewport.ec = 1 + posToColumn( _x + _radius );
		_viewport.er = 1 + posToRow( _z + _radius );
	}
}
