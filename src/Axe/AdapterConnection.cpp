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
	{
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveInvocation & AdapterConnection::beginMessage( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response )
	{
		ArchiveInvocation & ar = this->getArchiveInvocation();
		
		ar.begin();

		this->invokeMethod( ar, _servantId, _methodId, _response );

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
	void AdapterConnection::dispatchMessage( ArchiveDispatcher & _ar, std::size_t _size )
	{
		this->dispatchResponse( _ar, _size );

		_ar.clear();
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