#	pragma once

#	include "TypeVisitor.hpp"

#	include "TypeNumeric.hpp"
#	include "TypeString.hpp"
#	include "TypeArray.hpp"

namespace AxeProperty
{

	template<class Adapter>
	class TypeVisitorAdapter
		: public TypeVisitor
	{
	public:
		void process( TypeNumeric<bool> * _type ) override { process_adapter( _type ); }
		void process( TypeNumeric<int> * _type ) override { process_adapter( _type ); }
		void process( TypeNumeric<float> * _type ) override { process_adapter( _type ); }
		void process( TypeNumeric<double> * _type ) override { process_adapter( _type ); }

		void process( TypeString * _type ) override { process_adapter( _type ); }
		void process( TypeArray * _type ) override { process_adapter( _type ); }

	protected:
		template<class T>
		void process_adapter( T * _type )
		{
			static_cast<Adapter*>(this)->process( _type );
		}
	};
}