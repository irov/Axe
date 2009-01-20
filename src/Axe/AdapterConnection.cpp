#	include "pch.hpp"

#	include "AdapterConnection.hpp"

#	include "Session.hpp"
#	include "ArchiveWrite.hpp"
#	include "Adapter.hpp"
#	include "Response.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	AdapterConnection::AdapterConnection( boost::asio::io_service & _service )
		: SessionConnection(_service)
		, m_messageEnum(0)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveWrite & AdapterConnection::beginMessage( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response )
	{
		m_streamWrite->begin();

		this->write_body( _servantId, _methodId, _response );

		return *m_streamWrite;
	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t AdapterConnection::addDispatch( const ResponsePtr & _response )
	{
		if( m_dispatch.empty() )
		{
			m_messageEnum = 0;
		}

		++m_messageEnum;
		m_dispatch.insert( std::make_pair( m_messageEnum, _response ) );

		return m_messageEnum;
	}
	//////////////////////////////////////////////////////////////////////////
	void AdapterConnection::writeBody( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response )
	{
		std::size_t messageId = this->add_dispatch( _response );

		m_streamWrite->write_t( _servantId );
		m_streamWrite->writeSize( _methodId );
		m_streamWrite->writeSize( messageId );
	}
	//////////////////////////////////////////////////////////////////////////
	void AdapterConnection::dispatchMessage( std::size_t _size )
	{
		std::size_t responseId;
		m_streamIn->readSize( responseId );

		TMapResponse::iterator it_found = m_dispatch.find( responseId );

		const ResponsePtr & response = it_found->second;
		response->response_call( m_streamIn );

		m_dispatch.erase( it_found );

		m_streamIn->clear();
	}
}