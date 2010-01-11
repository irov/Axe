#	include "ClusterElement.hpp"

namespace AxeLib
{
	//////////////////////////////////////////////////////////////////////////
	ClusterElement::ClusterElement( std::size_t _elementId, float _radius )
		: m_elementId(_elementId)
		, m_elementRadius(_radius)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t ClusterElement::getElementId() const
	{
		return m_elementId;
	}
	//////////////////////////////////////////////////////////////////////////
	float ClusterElement::getElementRadius() const
	{
		return m_elementRadius;
	}
}
