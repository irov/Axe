#	pragma once

#	include <AxeUtil/Shared.hpp>

namespace AxeProperty
{
	class Observer
		: virtual public AxeUtil::Shared
	{
	public:
		virtual void onChangeValue() = 0;
	};

	typedef AxeHandle<Observer> ObserverPtr;
}