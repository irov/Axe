#	include "pch.hpp"

#	include <Axe/Connection.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Connection::Connection( std::size_t _hostId )
		: m_hostId(_hostId)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t Connection::getHostId() const
	{
		return m_hostId;
	}
}
