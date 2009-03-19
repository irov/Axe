#	include "pch.hpp"

#	include <Axe/AdapterSession.hpp>

#	include <Axe/Adapter.hpp>

#	include <Axe/ArchiveWrite.hpp>
#	include <Axe/ArchiveRead.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	AdapterSession::AdapterSession( boost::asio::io_service & _service, const HostPtr & _host, const ConnectionCachePtr & _connectionCache )
		: HostSession(_service, _host, _connectionCache)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void AdapterSession::permissionVerify( ArchiveRead & _ar, std::size_t _size )
	{
		this->beginConnect( true );
		this->process();
		this->run();
	}
}