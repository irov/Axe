#	pragma once

#	include <AxeUtil/Shared.hpp>
#	include <AxeUtil/ForeachPoolMap.hpp>

namespace AxeLib
{
	typedef AxeHandle<class ClusterElement> ClusterElementPtr;

	class Cluster
		: virtual public AxeUtil::Shared
	{
	public:
		void insertElement( const ClusterElementPtr & _element, bool _master );
		bool removeElement( const ClusterElementPtr & _element);

		void changeElementMaster( const ClusterElementPtr & _element, bool _master );

	public:
		struct ClusterElementState
		{
			ClusterElementPtr element;
			bool master;
		};

		typedef AxeUtil::ForeachPoolMap<ClusterElementState> TMapClusterElementState;
		inline const TMapClusterElementState & getClusterElements() const;

	protected:
		TMapClusterElementState m_elements;
	};
	//////////////////////////////////////////////////////////////////////////
	typedef AxeHandle<Cluster> ClusterPtr;
	//////////////////////////////////////////////////////////////////////////
	inline const Cluster::TMapClusterElementState & Cluster::getClusterElements() const
	{
		return m_elements;
	}
}
