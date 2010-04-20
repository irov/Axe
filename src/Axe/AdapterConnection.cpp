#	include "pch.hpp"

#	include <Axe/AdapterConnection.hpp>

#	include <Axe/Session.hpp>
#	include <Axe/Adapter.hpp>
#	include <Axe/Response.hpp>
#	include <Axe/Exception.hpp>

#	include <Axe/ArchiveInvocation.hpp>
#	include <Axe/ArchiveDispatcher.hpp>

#	include <Axe/DispatcherException.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	AdapterConnection::AdapterConnection( const SocketPtr & _socket, const ConnectionCachePtr & _connectionCache, std::size_t _adapterId, const EndpointCachePtr & _endpointCache )
		: Connection(_socket, _connectionCache)
		, m_adapterId(_adapterId)
		, m_endpointCache(_endpointCache)
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
	void AdapterConnection::write( ArchiveInvocation & _ar ) const
	{
		char connectionTypeId = 0;
		_ar.writePOD( connectionTypeId );

		_ar.write( m_adapterId );
	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t AdapterConnection::addDispatch( const ResponsePtr & _response )
	{
		if( _response == 0 )
		{
			return 0;
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
		std::size_t responseId;
		_ar.readSize( responseId );

		TMapResponse::iterator it_found = m_dispatch.find( responseId );

		if( it_found == m_dispatch.end() )
		{
			throw ProtocolMismatchException();
		}

		const ResponsePtr & response = it_found->second;

		if( response->dispatch( _ar, _size ) == true )
		{
			m_dispatch.erase( it_found );
		}

		if( m_dispatch.empty() )
		{
			m_messageEnum = 0;
		}

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
			, m_adapterId
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void AdapterConnection::_reconnect()
	{
		printf("Invocation::processMessage m_socket is closed, opening\n"
			);

		m_endpointCache->getEndpoint( m_adapterId, 
			boost::bind( &AdapterConnection::onEndpoint, handlePtr(this), _1 )
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void AdapterConnection::onEndpoint( const boost::asio::ip::tcp::endpoint & _endpoint )
	{
		this->connect( _endpoint );
	}
}