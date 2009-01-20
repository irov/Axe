#	include "pch.hpp"

#	include "RouterProxyConnection.hpp"
#	include "RouterConnection.hpp"
#	include "Response.hpp"

#	include "ArchiveWrite.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	RouterProxyConnection::RouterProxyConnection( const RouterConnectionPtr & _base, std::size_t _id )
		: m_base(_base)
		, m_id(_id)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveWrite & RouterProxyConnection::beginMessage( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response )
	{
		ArchiveWrite & stream 
			= m_base->beginMessage( _servantId, _methodId, _response );

		stream.writeSize( m_id );
	
		return stream;
	}
	//////////////////////////////////////////////////////////////////////////
	void RouterProxyConnection::process()
	{
		m_base->process();
	}
}