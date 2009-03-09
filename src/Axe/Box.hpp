#	pragma  once

#	include "Shared.hpp"

namespace Axe
{
	typedef AxeHandle<class Communicator> CommunicatorPtr;

	class Box
	{
		virtual bool start( const CommunicatorPtr & _communicator ) = 0;
		virtual void stop() = 0;
	}
}