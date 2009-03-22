#	include "pch.hpp"

#	include <Axe/Invocation.hpp>

#	include <Axe/ArchiveWrite.hpp>
#	include <Axe/ArchiveRead.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Invocation::Invocation( boost::asio::io_service & _service, std::size_t _hostId, const EndpointCachePtr & _endpointCache, const ConnectionCachePtr & _connectionCache )
		: Dispatcher(_service, _connectionCache)
		, Connection(_hostId)
		, m_endpointCache(_endpointCache)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveWrite & Invocation::connect( const boost::asio::ip::tcp::endpoint & _endpoint )
	{
		m_permission.begin();

		this->connect_( _endpoint, this );

		return m_permission;
	}
	//////////////////////////////////////////////////////////////////////////
	void Invocation::connect_( const boost::asio::ip::tcp::endpoint & _endpoint, const ConnectCallbackPtr & _cb )
	{
		m_socket.async_connect( _endpoint
			, boost::bind( &Invocation::handleConnect, handlePtr(this), boost::asio::placeholders::error, _cb ) 
			);
	}	
	//////////////////////////////////////////////////////////////////////////
	void Invocation::processMessage()
	{
		if( m_socket.is_open() == false )
		{
			m_endpointCache->getEndpoint( m_hostId, this );
		}
		else
		{
			this->process();
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void Invocation::handleConnect( const boost::system::error_code & _ec, const ConnectCallbackPtr & _cb )
	{
		if( _ec )
		{
			printf("Invocation::handleConnect ec: %s\n", _ec.message().c_str() );
			return;
		}

		if( m_permission.empty() == false )
		{
			const Archive & ar = m_permission.getArchive();

			this->processArchive( ar );
		}
		else
		{
			this->process();
		}

		std::size_t * size = m_streamIn.keep<std::size_t>();

		boost::asio::async_read( m_socket
			, boost::asio::buffer( size, sizeof(std::size_t) )
			, boost::bind( &Dispatcher::handleReadCondition, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, sizeof(std::size_t) )
			, boost::bind( &Invocation::handleReadConnectSize, handlePtr(this), boost::asio::placeholders::error, size, _cb )
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Invocation::handleReadConnectSize( const boost::system::error_code & _ec, std::size_t * _size, const ConnectCallbackPtr & _cb )
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
			, boost::bind( &Invocation::handleReadConnect, handlePtr(this), boost::asio::placeholders::error, blob, _cb )
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Invocation::handleReadConnect( const boost::system::error_code & _ec, Archive::value_type * _blob, const ConnectCallbackPtr & _cb )
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
			_cb->connectionSuccessful( m_streamIn, size );				
			this->run();
		}
		else
		{
			this->close();
			_cb->connectionFailed( m_streamIn, size );				
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void Invocation::onEndpoint( const boost::asio::ip::tcp::endpoint & _endpoint )
	{
		this->connect( _endpoint );
	}
}