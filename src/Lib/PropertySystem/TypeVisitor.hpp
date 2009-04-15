#	pragma once

namespace AxeProperty
{
	template<class T>
	class TypeNumeric;

	class TypeVisitor
	{
	public:
		virtual void process( class TypeNumeric<bool> * _type ) = 0;
		virtual void process( class TypeNumeric<int> * _type ) = 0;
		virtual void process( class TypeNumeric<float> * _type ) = 0;
		virtual void process( class TypeNumeric<double> * _type ) = 0;
		virtual void process( class TypeString * _type ) = 0;
		virtual void process( class TypeArray * _type ) = 0;
	};
}
