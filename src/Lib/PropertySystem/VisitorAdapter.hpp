#	pragma once

#	include "Visitor.hpp"

#	include "Arithmetics.hpp"
#	include "String.hpp"
#	include "Array.hpp"

namespace AxeProperty
{
	template<class Adapter>
	class VisitorAdapter
		: public Visitor
	{
	public:
		void process( Numeric<bool> * _type ) override { process_adapter( _type ); }
		void process( Numeric<int> * _type ) override { process_adapter( _type ); }
		void process( Numeric<float> * _type ) override { process_adapter( _type ); }
		void process( Numeric<double> * _type ) override { process_adapter( _type ); }

		void process( String * _type ) override { process_adapter( _type ); }
		void process( Array * _type ) override { process_adapter( _type ); }

	protected:
		template<class T>
		void process_adapter( T * _type )
		{
			static_cast<Adapter*>(this)->process( _type );
		}
	};
}