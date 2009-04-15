#	include "TypeString.hpp"
#	include "TypeVisitor.hpp"

#	include "String.hpp"

namespace AxeProperty
{
	//////////////////////////////////////////////////////////////////////////
	PROPERTY_TYPE_VISITOR_IMPLEMENT( TypeString );
	//////////////////////////////////////////////////////////////////////////
	TypeString::TypeString()
		: Type( "string" )
	{
	}
	//////////////////////////////////////////////////////////////////////////
	BasePtr TypeString::gen()
	{
		return new String( this );
	}		
}