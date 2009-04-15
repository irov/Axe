#	pragma once

#	include <AxeUtil/Shared.hpp>

#	include <string>

namespace AxeProperty
{
	class TypeVisitor;

	typedef AxeHandle<class Base> BasePtr;

	class Type
		: virtual public AxeUtil::Shared
	{
	public:
		Type( const std::string & _name );

	public:
		virtual BasePtr gen() = 0;

	public:
		const std::string & getName() const;

	public:
		virtual void visit( TypeVisitor * _visitor ) = 0;

	protected:
		std::string m_name;
	};

	typedef AxeHandle<Type> TypePtr;

#	define PROPERTY_TYPE_VISITOR_DECLARE()\
public:\
	void visit( TypeVisitor * _visitor );\
protected:

#	define PROPERTY_TYPE_VISITOR_IMPLEMENT( TYPE )\
	void TYPE::visit( TypeVisitor * _visitor )\
	{\
	_visitor->process( this );\
	}
}