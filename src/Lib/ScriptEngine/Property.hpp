#	pragma once

#	include "EmbeddingProperty.hpp"

#	include <AxeUtil/Shared.hpp>

namespace AxeScript
{
	class Property
		: virtual public AxeUtil::Shared
	{
	public:
		Property( const EmbeddingPropertyPtr & _embedding, const boost::python::object & _value );

	public:
		void update( const boost::python::object & _value );

	public:
		std::size_t getRevision() const;
		const boost::python::object & getValue() const;

	protected:
		std::size_t m_revision;
		EmbeddingPropertyPtr m_embedding;
		boost::python::object m_value;
	};

	typedef AxeHandle<Property> PropertyPtr;
}
