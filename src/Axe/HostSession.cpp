#	include "pch.hpp"

#	include "HostSession.hpp"

#	include "ArchiveWrite.hpp"
#	include "ArchiveRead.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	HostSession::HostSession( boost::asio::io_service & _service, const HostPtr & _host )
		: Session( _service )
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