#	include "pch.hpp"

#	include "AdapterSession.hpp"

#	include "Adapter.hpp"

#	include "ArchiveWrite.hpp"
#	include "ArchiveRead.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	AdapterSession::AdapterSession( boost::asio::io_service & _service, const AdapterPtr & _adapter )
		: Session( _service )
		, m_adapter(_adapter)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveWrite & AdapterSession::beginResponse( std::size_t _responseId )
	{
		ArchiveWrite & ar = this->getArchiveWrite();
		
		ar.begin();
		ar.writeSize( _responseId );

		return *m_streamWrite;
	}
	//////////////////////////////////////////////////////////////////////////
	void AdapterSession::dispatchMessage( std::size_t _size )
	{
		ArchiveRead & ar = this->getArchiveRead();

		std::size_t servantId;
		std::size_t methodId;
		std::size_t requestId;

		ar.read( servantId);
		ar.readSize( methodId);
		ar.readSize( requestId);

		m_adapter->dispatchMethod( servantId, methodId, requestId, this );
	}
}