#	include "pch.hpp"

#	include <Axe/Connection.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Connection::Connection( std::size_t _adapterId )
		: m_adapterId(_adapterId)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t Connection::getAdapterId() const
	{
		return m_adapterId;
	}
}
