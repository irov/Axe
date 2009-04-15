#	include "TypeArray.hpp"
#	include "TypeVisitor.hpp"

#	include "Array.hpp"

namespace AxeProperty
{
	//////////////////////////////////////////////////////////////////////////
	PROPERTY_TYPE_VISITOR_IMPLEMENT( TypeArray );
	//////////////////////////////////////////////////////////////////////////
	TypeArray::TypeArray( const TypePtr & _elementType )
		: Type( "array_of_" + _elementType->getName() )
		, m_elementType(_elementType)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	const TypePtr & TypeArray::getElementType() const
	{
		return m_elementType;
	}
	//////////////////////////////////////////////////////////////////////////
	BasePtr TypeArray::gen()
	{
		return new Array( this );
	}
}