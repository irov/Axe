#	include "pch.hpp"

#	include <Axe/RouterProxyConnection.hpp>

#	include <Axe/ArchiveWrite.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	RouterProxyConnection::RouterProxyConnection( const RouterConnectionPtr & _base, std::size_t _hostId )
		: Connection( _hostId )
		, m_base(_base)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveWrite & RouterProxyConnection::beginMessage( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response )
	{
		ArchiveWrite & ar 
			= m_base->beginMessage( _servantId, _methodId, _response );

		ar.writeSize( m_hostId );
	
		return ar;
	}
	//////////////////////////////////////////////////////////////////////////
	void RouterProxyConnection::processMessage()
	{
		m_base->process();
	}
}