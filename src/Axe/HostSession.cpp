#	include "pch.hpp"

#	include <Axe/HostSession.hpp>

#	include <Axe/ArchiveWrite.hpp>
#	include <Axe/ArchiveRead.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	HostSession::HostSession( boost::asio::io_service & _service, const HostPtr & _host, const ConnectionCachePtr & _connectionCache )
		: Session( _service, _connectionCache )
		, m_host(_host)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void HostSession::dispatchMessage( ArchiveRead & _ar, std::size_t _size )
	{
		std::size_t servantId;
		std::size_t methodId;
		std::size_t requestId;

		_ar.read( servantId);
		_ar.readSize( methodId);
		_ar.readSize( requestId);

		m_host->dispatchMethod( servantId, methodId, requestId, this );
	}
}