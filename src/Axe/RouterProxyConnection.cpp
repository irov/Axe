#	include "pch.hpp"

#	include <Axe/RouterProxyConnection.hpp>

#	include <Axe/ArchiveInvocation.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	RouterProxyConnection::RouterProxyConnection( const RouterConnectionPtr & _base )
		: Connection( _base->getSocket(), _base->getConnectionCache() )
		, m_base(_base)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveInvocation & RouterProxyConnection::beginMessage( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response )
	{
		ArchiveInvocation & ar 
			= m_base->beginMessage( _servantId, _methodId, _response );

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
	//////////////////////////////////////////////////////////////////////////
	void RouterProxyConnection::write( ArchiveInvocation & _ar ) const
	{
		m_base->write( _ar );

	}
}