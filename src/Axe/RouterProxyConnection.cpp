#	include "pch.hpp"

#	include "RouterProxyConnection.hpp"

#	include "ArchiveWrite.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	RouterProxyConnection::RouterProxyConnection( const RouterConnectionPtr & _base, std::size_t _endpointId )
		: Connection( _endpointId )
		, m_base(_base)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveWrite & RouterProxyConnection::beginMessage( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response )
	{
		ArchiveWrite & stream 
			= m_base->beginMessage( _servantId, _methodId, _response );

		stream.writeSize( m_endpointId );
	
		return stream;
	}
	//////////////////////////////////////////////////////////////////////////
	void RouterProxyConnection::processMessage()
	{
		m_base->process();
	}
}