#	include "pch.hpp"

#	include "Connection.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Connection::Connection( std::size_t _endpointId )
		: m_endpointId(_endpointId)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t Connection::getEndpointId() const
	{
		return m_endpointId;
	}
}
