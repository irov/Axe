#	include "Numeric.hpp"
#	include "Visitor.hpp"

namespace AxeProperty
{
	////////////////////////////////////////////////////////////////////////
	template<>
	void Numeric<bool>::visit( Visitor * _visitor )
	{
		_visitor->process( this );
	}
	////////////////////////////////////////////////////////////////////////
	template<>
	void Numeric<int>::visit( Visitor * _visitor )
	{
		_visitor->process( this );
	}
	////////////////////////////////////////////////////////////////////////
	template<>
	void Numeric<float>::visit( Visitor * _visitor )
	{
		_visitor->process( this );
	}
	////////////////////////////////////////////////////////////////////////
	template<>
	void Numeric<double>::visit( Visitor * _visitor )
	{
		_visitor->process( this );
	}
}
