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
	AdapterConnection::AdapterConnection( boost::asio::io_service & _service, std::size_t _hostId, const EndpointCachePtr & _endpointCache, const ConnectionCachePtr & _connectionCache )
		: Invocation(_service, _hostId, _endpointCache, _connectionCache)
		, m_messageEnum(0)
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
		bool true_response;
		_ar.read( true_response );

		std::size_t responseId;
		_ar.readSize( responseId );

		TMapResponse::iterator it_found = m_dispatch.find( responseId );

		const ResponsePtr & response = it_found->second;

		if( true_response )
		{
			response->responseCall( _ar, _size );
		}
		else
		{
			response->exceptionCall( _ar, _size );
		}

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