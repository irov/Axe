#	pragma  once

#	include <AxeUtil/Shared.hpp>

namespace Axe
{
	typedef AxeHandle<class Communicator> CommunicatorPtr;

	class Box
		: virtual public AxeUtil::Shared
	{
		virtual bool start( const CommunicatorPtr & _communicator ) = 0;
		virtual void stop() = 0;
	}
}