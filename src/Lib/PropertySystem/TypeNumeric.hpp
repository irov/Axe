#	pragma once

#	include <typeinfo>

#	include "Type.hpp"

#	include "Numeric.hpp"

namespace AxeProperty
{
	template<class T>
	class TypeNumeric
		: public Type
	{
	public:
		TypeNumeric()
			: Type( typeid(T).name() )
		{
		}

	public:
		BasePtr gen() override
		{
			return new Numeric<T>( this );
		}

		void visit( TypeVisitor * _visitor ) override;
	};

	//typedef TypeNumeric<bool> TypeBool;
	//typedef TypeNumeric<int> TypeInt;
	//typedef TypeNumeric<float> TypeFloat;
	//typedef TypeNumeric<double> TypeDouble;

	//typedef AxeHandle<TypeBool> TypeBoolPtr;
	//typedef AxeHandle<TypeInt> TypeIntPtr;
	//typedef AxeHandle<TypeFloat> TypeFloatPtr;
	//typedef AxeHandle<TypeDouble> TypeDoublePtr;
}
