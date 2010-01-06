#	include "pch.hpp"

#	include <Axe/Invocation.hpp>

#	include <Axe/ArchiveInvocation.hpp>
#	include <Axe/ArchiveDispatcher.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Invocation::Invocation( boost::asio::io_service & _service, std::size_t _hostId, const EndpointCachePtr & _endpointCache, const ConnectionCachePtr & _connectionCache )
		: Dispatcher(_service, _connectionCache)
		, Connection(_hostId)
		, m_endpointCache(_endpointCache)
		, m_permission(_connectionCache)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveInvocation & Invocation::connect( const boost::asio::ip::tcp::endpoint & _endpoint )
	{
		m_permission.begin();

		printf("Invocation::connect host %d - endpoint %s\n"
			, m_hostId
			, _endpoint.address().to_string().c_str()
			);

		m_socket.async_connect( _endpoint
			, boost::bind( &Invocation::handleConnect, handlePtr(this), boost::asio::placeholders::error ) 
			);

		return m_permission;
	}
	//////////////////////////////////////////////////////////////////////////
	void Invocation::processMessage()
	{
		printf("Invocation::processMessage host %d\n"
			, m_hostId
			);

		if( m_socket.is_open() == false )
		{
			printf("Invocation::processMessage m_socket is closed, opening\n"
				);

			m_endpointCache->getEndpoint( m_hostId, this );
		}
		else
		{
			printf("Invocation::processMessage process\n"
				);
			this->process();
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void Invocation::handleConnect( const boost::system::error_code & _ec )
	{
		if( _ec )
		{
			printf("Invocation::handleConnect ec: host %d ec %s\n"
				, m_hostId
				, _ec.message().c_str() 
				);
			return;
		}

		printf("Invocation::handleConnect host %d\n"
			, m_hostId
			);

		if( m_permission.empty() == false )
		{
			printf("Invocation::handleConnect send permission \n"
				);

			const AxeUtil::Archive & ar = m_permission.getArchive();

			this->processArchive( ar );
		}

		std::size_t * size = m_streamIn.keep<std::size_t>();

		boost::asio::async_read( m_socket
			, boost::asio::buffer( size, sizeof(std::size_t) )
			, boost::bind( &Dispatcher::handleReadCondition, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, sizeof(std::size_t) )
			, boost::bind( &Invocation::handleReadConnectSize, handlePtr(this), boost::asio::placeholders::error, size )
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

		AxeUtil::Archive::value_type * blob = m_streamIn.keepBuffer( size_blob );

		boost::asio::async_read( m_socket
			, boost::asio::buffer( blob, size_blob )
			, boost::bind( &Dispatcher::handleReadCondition, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, size_blob )
			, boost::bind( &Invocation::handleReadConnect, handlePtr(this), boost::asio::placeholders::error, blob )
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Invocation::handleReadConnect( const boost::system::error_code & _ec, AxeUtil::Archive::value_type * _blob )
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

		printf("Invocation::handleReadConnect host - %d size - %d, result - %d\n"
			, m_hostId
			, size
			, (int)result
			);

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
	void Invocation::onEndpoint( const boost::asio::ip::tcp::endpoint & _endpoint )
	{
		m_permission.clear();

		this->connect( _endpoint );
	}
}