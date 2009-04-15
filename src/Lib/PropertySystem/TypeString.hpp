#	pragma once

#	include "Type.hpp"

namespace AxeProperty
{
	class TypeString
		: public Type
	{
		PROPERTY_TYPE_VISITOR_DECLARE();

	public:
		TypeString();

	public:
		BasePtr gen() override;
	};

	typedef AxeHandle<TypeString> TypeStringPtr;
}