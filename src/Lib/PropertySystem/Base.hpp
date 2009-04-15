#	pragma once

#	include <AxeUtil/Shared.hpp>

#	include "Type.hpp"
#	include "Observer.hpp"

#	include <vector>

namespace AxeProperty
{
	class Visitor;

	class Base
		: virtual public AxeUtil::Shared
	{
	public:
		Base( const TypePtr & _type );

	public:
		const TypePtr & getType() const;

	public:
		void addObserver( const ObserverPtr & _observer );

	public:
		virtual void changeValue();
		virtual void finialize();

	public:
		virtual void visit( Visitor * _visitor ) = 0;

	protected:
		TypePtr m_type;

		typedef std::vector<ObserverPtr> TVectorObservers;
		TVectorObservers m_observers;
	};

	typedef AxeHandle<Base> BasePtr;

#	define PROPERTY_VISITOR_DECLARE()\
public:\
	void visit( Visitor * _visitor ) override;\
private:

#	define PROPERTY_VISITOR_IMPLEMENT( TYPE )\
	void TYPE::visit( Visitor * _visitor )\
	{\
	_visitor->process( this );\
	}
}