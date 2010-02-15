#	pragma once

#	include <AxeUtil/Shared.hpp>

namespace Axe
{
	typedef AxeHandle<class Communicator> CommunicatorPtr;

	class Host
	{
	public:
		Host( const boost::property_tree::ptree & _pr );

	public:
		void run();

	protected:
		CommunicatorPtr m_communicator;
	};
}