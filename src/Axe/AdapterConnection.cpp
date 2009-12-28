#	include "pch.hpp"

#	include <Axe/AdapterConnection.hpp>

#	include <Axe/Session.hpp>
#	include <Axe/Adapter.hpp>
#	include <Axe/Response.hpp>

#	include <Axe/ArchiveInvocation.hpp>
#	include <Axe/ArchiveDispatcher.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	AdapterConnection::AdapterConnection( boost::asio::io_service & _service, std::size_t _hostId, const EndpointCachePtr & _endpointCache, const ConnectionCachePtr & _connectionCache )
		: Invocation(_service, _hostId, _endpointCache, _connectionCache)
		, m_messageEnum(0)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveInvocation & AdapterConnection::beginMessage( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response )
	{
		ArchiveInvocation & ar = this->getArchiveInvocation();
		
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
	void AdapterConnection::writeBody( ArchiveInvocation & _archive, std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response )
	{
		std::size_t messageId = this->addDispatch( _response );

		_archive << _servantId;

		_archive.writeSize( _methodId );
		_archive.writeSize( messageId );
	}
	//////////////////////////////////////////////////////////////////////////
	void AdapterConnection::dispatchMessage( ArchiveDispatcher & _ar, std::size_t _size )
	{
		bool true_response;
		_ar.read( true_response );

		std::size_t responseId;
		_ar.readSize( responseId );

		TMapResponse::iterator it_found = m_dispatch.find( responseId );

		if( it_found == m_dispatch.end() )
		{
			throw CriticalException("AdapterConnection::dispatchMessage unknown responseId");
		}

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
	void AdapterConnection::connectionSuccessful( ArchiveDispatcher & _ar, std::size_t _size )
	{
		
	}
	//////////////////////////////////////////////////////////////////////////
	void AdapterConnection::connectionFailed( ArchiveDispatcher & _ar, std::size_t _size )
	{
		printf("Invocation::connectionFailed %d \n"
			, m_hostId
			);
	}
}