#	include "pch.hpp"

#	include <Axe/RouterProxyConnection.hpp>

#	include <Axe/ArchiveInvocation.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	RouterProxyConnection::RouterProxyConnection( const RouterConnectionPtr & _base, std::size_t _adapterId )
		: Connection( _base->getSocket(), _base->getConnectionCache(), _adapterId )
		, m_base(_base)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveInvocation & RouterProxyConnection::beginMessage( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response )
	{
		ArchiveInvocation & ar 
			= m_base->beginMessage( _servantId, _methodId, _response );

		std::size_t adapterId = this->getAdapterId();

		ar.writeSize( adapterId );
	
		return ar;
	}
	//////////////////////////////////////////////////////////////////////////
	void RouterProxyConnection::connectionSuccessful( ArchiveDispatcher & _ar, std::size_t _size )
	{
		//Empty
	}
	//////////////////////////////////////////////////////////////////////////
	void RouterProxyConnection::connectionFailed( ArchiveDispatcher & _ar, std::size_t _size )
	{
		//Empty
	}
	//////////////////////////////////////////////////////////////////////////
	void RouterProxyConnection::dispatchMessage( ArchiveDispatcher & _ar, std::size_t _size )
	{
		//Empty
	}
}