#	include "Base.hpp"

#	include "Type.hpp"
#	include "Observer.hpp"

#	include <algorithm>

namespace AxeProperty
{
	//////////////////////////////////////////////////////////////////////////
	Base::Base( const TypePtr & _type )
		: m_type(_type)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Base::finialize()
	{
		m_observers.clear();
	}
	//////////////////////////////////////////////////////////////////////////
	const TypePtr & Base::getType() const
	{
		return m_type;
	}
	//////////////////////////////////////////////////////////////////////////
	void Base::addObserver( const ObserverPtr & _observer )
	{
		m_observers.push_back( _observer );
	}
	//////////////////////////////////////////////////////////////////////////
	void Base::changeValue()
	{
		if( m_observers.empty() == false )
		{
			for( TVectorObservers::iterator
				it = m_observers.begin(),
				it_end = m_observers.end();
			it != it_end;
			++it )
			{
				(*it)->onChangeValue();
			}
		}
	}
}