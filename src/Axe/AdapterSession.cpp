#	include "pch.hpp"

#	include <Axe/AdapterSession.hpp>

#	include <Axe/Adapter.hpp>

#	include <Axe/ArchiveInvocation.hpp>
#	include <Axe/ArchiveDispatcher.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	AdapterSession::AdapterSession( const SocketPtr & _socket, const ConnectionCachePtr & _connectionCache, const AdapterPtr & _adapter )
		: Session(_socket, _connectionCache)
		, m_adapter(_adapter)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void AdapterSession::dispatchMessage( ArchiveDispatcher & _ar, std::size_t _size )
	{
		std::size_t servantId;
		std::size_t methodId;
		std::size_t requestId;

		_ar.read( servantId );
		_ar.readSize( methodId );
		_ar.readSize( requestId );

		m_adapter->dispatchMethod( servantId, methodId, requestId, _ar, this );
	}
	//////////////////////////////////////////////////////////////////////////
	void AdapterSession::permissionVerify( ArchiveDispatcher & _ar, std::size_t _size )
	{
		this->beginConnect( true );
		this->process();
		this->run();
	}
}