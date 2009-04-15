#	pragma once

#	include "Base.hpp"

namespace AxeProperty
{
	template<class T>
	class Numeric
		: public Base
	{
	public:
		typedef T value_type;

	public:
		Numeric( const TypePtr & _type )
			: Base(_type)
		{
		}

		~Numeric()
		{
		}

	public:
		const T * begin() const
		{
			return &m_value;
		}

		const T * end() const
		{
			return (&m_value + 1);
		}

		void setValue( T _value )
		{
			m_value = _value;
		}

		T getValue() const
		{
			return m_value;
		}

	public:
		void visit( Visitor * _visitor ) override;

	protected:
		T m_value;
	};

	//typedef Numeric<bool> Bool;
	//typedef Numeric<int> Int;
	//typedef Numeric<float> Float;
	//typedef Numeric<double> Double;

	//typedef AxeHandle<Bool> BoolPtr;
	//typedef AxeHandle<Int> IntPtr;
	//typedef AxeHandle<Float> FloatPtr;
	//typedef AxeHandle<Double> DoublePtr;
}