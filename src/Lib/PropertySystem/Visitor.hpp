#	pragma once

namespace AxeProperty
{
	template<class T>
	class Numeric;

	class Visitor
	{
	public:
		virtual void process( class Numeric<bool> * _type ) = 0;
		virtual void process( class Numeric<int> * _type ) = 0;
		virtual void process( class Numeric<float> * _type ) = 0;
		virtual void process( class Numeric<double> * _type ) = 0;

		virtual void process( class String * _type ) = 0;
		virtual void process( class Array * _type ) = 0;
	};
}
