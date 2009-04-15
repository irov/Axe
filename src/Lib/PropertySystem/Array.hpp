#	pragma once

#	include "Base.hpp"

#	include <vector>

namespace AxeProperty
{
	typedef std::vector<BasePtr> TVectorElements;

	class Array
		: public Base
	{
		PROPERTY_VISITOR_DECLARE()

	public:
		Array( const TypePtr & _type );

	public:
		void clearValue();
		
	public:
		void addElement( const BasePtr & _property );
		const BasePtr & getElement( std::size_t _index ) const;

	public:
		const TVectorElements & getElements() const;
		std::size_t countElement() const;		

	protected:
		TVectorElements m_array;
	};

	typedef AxeHandle<Array> ArrayPtr;
}