#	pragma once

#	include "Base.hpp"

#	include <string>

namespace AxeProperty
{
	class String
		: public Base
	{
		PROPERTY_VISITOR_DECLARE()

	public:
		String( const TypePtr & _type );

	public:
		void setValue( const std::string & _value );
		const std::string & getValue() const;

	protected:
		std::string m_value;
	};

	typedef AxeHandle<String> StringPtr;
}