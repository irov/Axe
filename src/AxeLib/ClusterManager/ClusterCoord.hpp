#	pragma once

#	include <functional>

#	include <math.h>

namespace AxeLib
{
	struct ClusterCoord
	{
		int row;
		int column;
	};

	//////////////////////////////////////////////////////////////////////////
	inline int floori( float _arg )
	{
		return int( floorf( _arg ) );
	}

	//////////////////////////////////////////////////////////////////////////
	struct ClusterViewport
	{
		int bc;
		int br;
		int ec;
		int er;
	};

	//////////////////////////////////////////////////////////////////////////
	inline bool testPoint( const ClusterViewport & _viewport, int row, int column )
	{
		if( _viewport.br > row ) return false;
		if( _viewport.bc > column ) return false;
		if( _viewport.er <= row ) return false;
		if( _viewport.ec <= column ) return false;

		return true;
	}

	struct ClusterCoordLess
		: public std::binary_function<ClusterCoord, ClusterCoord, bool>
	{
		bool operator() ( const ClusterCoord & _left, const ClusterCoord & _right ) const
		{
			if( _left.row == _right.row )
			{
				return ( _left.column < _right.column );
			}

			return ( _left.row < _right.row );
		}
	};
}

