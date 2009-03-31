#	include "pch.hpp"

#	include "Property.hpp"

namespace AxeScript
{
	//////////////////////////////////////////////////////////////////////////
	Property::Property( const EmbeddingPropertyPtr & _embedding, const boost::python::object & _value )
		: m_embedding(_embedding)
		, m_value(_value)
		, m_revision(0)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Property::update( const boost::python::object & _value )
	{
		++m_revision;
		m_value = _value;
	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t Property::getRevision() const
	{
		return m_revision;
	}
	//////////////////////////////////////////////////////////////////////////
	const boost::python::object & Property::getValue() const
	{
		return m_value;
	}
}
