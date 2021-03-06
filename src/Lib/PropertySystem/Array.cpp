#	include "Array.hpp"

#	include "Visitor.hpp"

namespace AxeProperty
{
	//////////////////////////////////////////////////////////////////////////
	PROPERTY_VISITOR_IMPLEMENT(Array);
	//////////////////////////////////////////////////////////////////////////
	Array::Array( const TypePtr & _type )
		: Base( _type )
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Array::clearValue()
	{
		m_array.clear();
	}
	//////////////////////////////////////////////////////////////////////////
	void Array::addElement( const BasePtr & _property )
	{
		m_array.push_back( _property );
	}
	//////////////////////////////////////////////////////////////////////////
	const BasePtr & Array::getElement( std::size_t _index ) const
	{
		const BasePtr & property = m_array[ _index ];

		return property;
	}
	//////////////////////////////////////////////////////////////////////////
	const TVectorElements & Array::getElements() const
	{
		return m_array;
	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t Array::countElement() const
	{
		std::size_t size = m_array.size();
		return size;
	}
}