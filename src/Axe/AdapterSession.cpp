#	include "pch.hpp"

#	include "AdapterSession.hpp"

#	include "Adapter.hpp"

#	include "ArchiveWrite.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	AdapterSession::AdapterSession( boost::asio::io_service & _service, const AdapterPtr & _adapter )
		: Session(_service)
		, m_adapter(_adapter)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveWrite & AdapterSession::beginResponse( std::size_t _responseId )
	{
		m_streamWrite->begin();
		m_streamWrite->writeSize( _responseId );

		return *m_streamWrite;
	}

	void AdapterSession::dispatchMessage( std::size_t _size )
	{
		std::size_t servantId;
		std::size_t methodId;
		std::size_t requestId;

		m_streamIn->read_t( servantId);
		m_streamIn->readSize( methodId);
		m_streamIn->readSize( requestId);

		m_adapter->dispatchMethod( servantId, methodId, requestId, this );
	}
}