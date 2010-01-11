#	pragma once

#	include <AxeUtil/Shared.hpp>

namespace AxeLib
{
	class ClusterElement
		: virtual public AxeUtil::Shared
	{
	public:
		ClusterElement( std::size_t _elementId, float _radius );

	public:
		std::size_t getElementId() const;
		float getElementRadius() const;

	protected:
		std::size_t m_elementId;
		float m_elementRadius;
	};

	typedef AxeHandle<ClusterElement> ClusterElementPtr;
}
