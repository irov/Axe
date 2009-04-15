#	pragma once

#	include "Type.hpp"

namespace AxeProperty
{
	class TypeArray
		: public Type
	{
		PROPERTY_TYPE_VISITOR_DECLARE();

	public:
		TypeArray( const TypePtr & _elementType );

	public:
		const TypePtr & getElementType() const;

	public:
		BasePtr gen() override;

	protected:
		TypePtr m_elementType;
	};

	typedef AxeHandle<TypeArray> TypeArrayPtr;
}