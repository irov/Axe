#	include "pch.hpp"

#	include "AdapterSession.hpp"

#	include "Adapter.hpp"

#	include "ArchiveWrite.hpp"
#	include "ArchiveRead.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	AdapterSession::AdapterSession( boost::asio::io_service & _service, const HostPtr & _host )
		: HostSession(_service, _host)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void AdapterSession::permissionVerify( ArchiveRead & _ar, std::size_t _size )
	{
		this->beginConnect( true );
		this->process();
	}
}