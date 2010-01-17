#	include "pch.hpp"

#	include <Axe/RouterProxyConnection.hpp>

#	include <Axe/ArchiveInvocation.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	RouterProxyConnection::RouterProxyConnection( const RouterConnectionPtr & _base, std::size_t _adapterId )
		: Connection( _adapterId )
		, m_base(_base)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveInvocation & RouterProxyConnection::beginMessage( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response )
	{
		ArchiveInvocation & ar 
			= m_base->beginMessage( _servantId, _methodId, _response );

		ar.writeSize( m_adapterId );
	
		return ar;
	}
	//////////////////////////////////////////////////////////////////////////
	void RouterProxyConnection::processMessage()
	{
		m_base->process();
	}
}