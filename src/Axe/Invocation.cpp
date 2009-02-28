#	include "pch.hpp"

#	include "Invocation.hpp"

#	include "ArchiveWrite.hpp"
#	include "ArchiveRead.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Invocation::Invocation( boost::asio::io_service & _service, std::size_t _hostId, const EndpointCachePtr & _endpointCache )
		: Dispatcher(_service)
		, Connection(_hostId)
		, m_endpointCache(_endpointCache)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveWrite & Invocation::connect( const boost::asio::ip::tcp::endpoint & _endpoint )
	{
		m_socket.async_connect( _endpoint
			, boost::bind( &Invocation::handleConnectRead, intrusivePtr(this), boost::asio::placeholders::error ) 
			);

		m_streamWrite.begin();

		return m_streamWrite;
	}
	//////////////////////////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////////
	void Invocation::processMessage()
	{
		if( m_socket.is_open() == false )
		{
			m_endpointCache->getEndpoint( m_hostId, this );
		}

		this->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Invocation::handleConnectRead( const boost::system::error_code & _ec )
	{
		if( _ec )
		{
			printf("Invocation::handleConnect ec: %s\n", _ec.message().c_str() );
			return;
		}

		std::size_t * size = m_streamIn.keep<std::size_t>();

		boost::asio::async_read( m_socket
			, boost::asio::buffer( size, sizeof(std::size_t) )
			, boost::bind( &Dispatcher::handleReadCondition, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, sizeof(std::size_t) )
			, boost::bind( &Invocation::handleReadConnectSize, intrusivePtr(this), boost::asio::placeholders::error, size )
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Invocation::handleReadConnectSize( const boost::system::error_code & _ec, std::size_t * _size )
	{
		if( _ec )
		{
			printf("Invocation::handleReadConnectSize ec: %s\n", _ec.message().c_str() );
			return;
		}

		std::size_t size_blob = *_size - sizeof(std::size_t);

		Archive::value_type * blob = m_streamIn.keepBuffer( size_blob );

		boost::asio::async_read( m_socket
			, boost::asio::buffer( blob, size_blob )
			, boost::bind( &Dispatcher::handleReadCondition, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, size_blob )
			, boost::bind( &Invocation::handleReadConnect, intrusivePtr(this), boost::asio::placeholders::error, blob )
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Invocation::handleReadConnect( const boost::system::error_code & _ec, Archive::value_type * _blob )
	{
		if( _ec )
		{
			printf("Invocation::handleReadConnect ec: %s\n", _ec.message().c_str() );
			return;
		}

		m_streamIn.begin();

		std::size_t size;
		m_streamIn.read( size );

		bool result;
		m_streamIn.read( result );

		if( result == true )
		{				
			this->connectionSuccessful( m_streamIn, size );				
			this->run();
		}
		else
		{
			this->close();
			this->connectionFailed( m_streamIn, size );				
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void Invocation::handleConnectProcess( const boost::system::error_code & _ec )
	{
		if( _ec )
		{
			printf("Invocation::handleConnect ec: %s\n", _ec.message().c_str() );
			return;
		}

		this->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Invocation::onEndpoint( const boost::asio::ip::tcp::endpoint & _endpoint )
	{
		m_socket.async_connect( _endpoint
			, boost::bind( &Invocation::handleConnectProcess, intrusivePtr(this), boost::asio::placeholders::error ) 
			);
	}
}