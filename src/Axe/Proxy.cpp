#	include "pch.hpp"

#	include "Proxy.hpp"
#	include "Connection.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Proxy::Proxy( std::size_t _servantId, const ConnectionPtr & _connection )
		: m_servantId(_servantId)
		, m_connection(_connection)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveWrite & Proxy::beginMessage( std::size_t _methodId, const ResponsePtr & _response )
	{
		ArchiveWrite & ar = m_connection->beginMessage( m_servantId, _methodId, _response );

		return ar;
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy::procces()
	{
		m_connection->procces();
	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t Proxy::getServantId() const
	{
		return m_servantId;
	}
}