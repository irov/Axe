#	include "Cluster.hpp"
#	include "ClusterElement.hpp"

namespace AxeLib
{
	//////////////////////////////////////////////////////////////////////////
	void Cluster::insertElement( const ClusterElementPtr & _element, bool _master )
	{
		ClusterElementState state;

		state.element = _element;
		state.master = _master;

		std::size_t id = _element->getElementId();

		m_elements.insert( id, state );
	}
	//////////////////////////////////////////////////////////////////////////
	bool Cluster::removeElement( const ClusterElementPtr & _element )
	{
		std::size_t id = _element->getElementId();

		ClusterElementState & state = m_elements[id];
		bool master = state.master;

		m_elements.erase( id );

		return master;
	}
	//////////////////////////////////////////////////////////////////////////
	void Cluster::changeElementMaster( const ClusterElementPtr & _element, bool _master )
	{
		std::size_t id = _element->getElementId();

		ClusterElementState & state = m_elements[id];

		state.master = _master;
	}
}
