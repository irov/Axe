#	include "TypeNumeric.hpp"
#	include "TypeVisitor.hpp"

namespace AxeProperty
{
	////////////////////////////////////////////////////////////////////////
	template<>
	void TypeNumeric<bool>::visit( TypeVisitor * _visitor )
	{
		_visitor->process( this );
	}
	////////////////////////////////////////////////////////////////////////
	template<>
	void TypeNumeric<int>::visit( TypeVisitor * _visitor )
	{
		_visitor->process( this );
	}
	////////////////////////////////////////////////////////////////////////
	template<>
	void TypeNumeric<float>::visit( TypeVisitor * _visitor )
	{
		_visitor->process( this );
	}
	////////////////////////////////////////////////////////////////////////
	template<>
	void TypeNumeric<double>::visit( TypeVisitor * _visitor )
	{
		_visitor->process( this );
	}
}
