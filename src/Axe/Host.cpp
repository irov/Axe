#	include "pch.hpp"

#	include "Host.hpp"

#	include "Communicator.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Host::Host( const boost::property_tree::ptree & _pr )
		: m_communicator( new Communicator( _pr ) )
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Host::run()
	{
		
	}
}