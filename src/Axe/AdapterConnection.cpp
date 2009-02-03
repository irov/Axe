#	include "pch.hpp"

#	include "AdapterConnection.hpp"

#	include "Session.hpp"
#	include "Adapter.hpp"
#	include "Response.hpp"

#	include "ArchiveWrite.hpp"
#	include "ArchiveRead.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	AdapterConnection::AdapterConnection( boost::asio::io_service & _service, const ConnectionCachePtr & _connectionCache, std::size_t _endpointId )
		: Invocation( _service, _endpointId )
		, m_messageEnum(0)
		, m_connectionCache(_connectionCache)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveWrite & AdapterConnection::beginMessage( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response )
	{
		ArchiveWrite & ar = this->getArchiveWrite();
		
		ar.begin();

		this->writeBody( ar, _servantId, _methodId, _response );

		return ar;
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
	void AdapterConnection::writeBody( ArchiveWrite & _archive, std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response )
	{
		std::size_t messageId = this->addDispatch( _response );

		_archive.write( _servantId );
		_archive.writeSize( _methodId );
		_archive.writeSize( messageId );
	}
	//////////////////////////////////////////////////////////////////////////
	void AdapterConnection::dispatchMessage( ArchiveRead & _ar, std::size_t _size )
	{
		std::size_t responseId;
		_ar.readSize( responseId );

		TMapResponse::iterator it_found = m_dispatch.find( responseId );

		const ResponsePtr & response = it_found->second;
		response->responseCall( _ar, m_connectionCache );

		m_dispatch.erase( it_found );

		_ar.clear();
	}
	//////////////////////////////////////////////////////////////////////////
	void AdapterConnection::connectionSuccessful( ArchiveRead & _ar, std::size_t _size )
	{
		
	}
	//////////////////////////////////////////////////////////////////////////
	void AdapterConnection::connectionFailed( ArchiveRead & _ar, std::size_t _size )
	{

	}
}