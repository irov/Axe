#	include "pch.hpp"

#	include "Connection.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Connection::Connection( const SocketPtr & _socket, const ConnectionCachePtr & _connectionCache )
		: m_socket(_socket)
		, m_connectionCache(_connectionCache)
		, m_permission(_connectionCache)
		, m_streamIn(_connectionCache)
		, m_streamOut(_connectionCache)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	const SocketPtr & Connection::getSocket() const
	{
		return m_socket;
	}
	//////////////////////////////////////////////////////////////////////////
	const ConnectionCachePtr & Connection::getConnectionCache() const
	{
		return m_connectionCache;
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveInvocation & Connection::getArchiveInvocation()
	{
		return m_streamOut;
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveInvocation & Connection::connect( const boost::asio::ip::tcp::endpoint & _endpoint, FConnectionConnect _response )
	{
		m_permission.clear();
		m_permission.begin();

		printf("Connection::connect endpoint %s\n"
			, _endpoint.address().to_string().c_str()
			);

		m_socket->connect( _endpoint
			, boost::bind( &Connection::handleConnect, handlePtr(this), boost::asio::placeholders::error, _response ) 
			);

		return m_permission;
	}
	//////////////////////////////////////////////////////////////////////////
	void Connection::close()
	{
		m_socket->close();
	}
	//////////////////////////////////////////////////////////////////////////
	void Connection::run()
	{
		m_streamIn.clear();
		m_streamIn.begin();

		std::size_t * size = m_streamIn.keep<std::size_t>();

		//boost::asio::async_read( m_socket
		//	, boost::asio::buffer( size, sizeof(std::size_t) )
		//	, boost::bind( &Dispatcher::handleReadCondition, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, sizeof(std::size_t) )
		//	, boost::bind( &Dispatcher::handleReadBodySize, handlePtr(this), boost::asio::placeholders::error, size )
		//	);

		m_socket->read( size, sizeof(size)
			, boost::bind( &Dispatcher::handleReadBodySize, handlePtr(this), boost::asio::placeholders::error, size ) 
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Connection::process()
	{
		if( m_socket->is_open() == false )
		{
			_reconnect();
			return;
		}

		if( m_archiveSend.empty() )
		{
			m_streamOut.swap( m_archiveSend );

			this->processArchive( m_archiveSend );
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void Connection::_reconnect()
	{
		//Empty;
	}
	//////////////////////////////////////////////////////////////////////////
	void Connection::processArchive( const AxeUtil::Archive & _ar )
	{
		m_socket->write_arhive( _ar
			, boost::bind( &Connection::handleWriteStream, handlePtr(this), boost::asio::placeholders::error )
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Connection::handleWriteStream( const boost::system::error_code & _ec )
	{
		if( _ec )
		{
			printf("Connection::handleWriteStream ec: %s\n"
				, _ec.message().c_str() 
				);

			return;
		}

		m_archiveSend.clear();

		if( m_streamOut.empty() == false )
		{
			this->process();
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void Connection::handleConnect( const boost::system::error_code & _ec, FConnectionConnect _response )
	{
		if( _ec )
		{
			printf("Connection::handleConnect ec: %s\n"
				, _ec.message().c_str() 
				);

			_response( ECS_ERROR, m_streamIn, 0 );
			return;
		}

		printf("Connection::handleConnect successful\n"
			);

		if( m_permission.empty() == false )
		{
			printf("Connection::handleConnect send permission \n"
				);

			const AxeUtil::Archive & ar = m_permission.getArchive();

			this->processArchive( ar );
		}

		std::size_t * size = m_streamIn.keep<std::size_t>();

		m_socket->read( size, sizeof(std::size_t)
			, boost::bind( &Connection::handleReadConnectSize, handlePtr(this), boost::asio::placeholders::error, size, _response )
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Connection::handleReadConnectSize( const boost::system::error_code & _ec, std::size_t * _size, FConnectionConnect _response )
	{
		if( _ec )
		{
			printf("Connection::handleReadConnectSize ec: %s\n"
				, _ec.message().c_str() 
				);

			this->close();
			_response( ECS_ERROR, m_streamIn, 0 );

			return;
		}

		std::size_t blob_size = *_size - sizeof(std::size_t);

		AxeUtil::Archive::value_type * blob = m_streamIn.keepBuffer( blob_size );

		m_socket->read( blob, blob_size
			, boost::bind( &Connection::handleReadConnect, handlePtr(this), boost::asio::placeholders::error, blob, _response )
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Connection::handleReadConnect( const boost::system::error_code & _ec, AxeUtil::Archive::value_type * _blob, FConnectionConnect _response )
	{
		if( _ec )
		{
			printf("Connection::handleReadConnect ec: %s\n", _ec.message().c_str() );

			this->close();
			_response( ECS_ERROR, m_streamIn, 0 );

			return;
		}

		m_streamIn.begin();

		std::size_t size;
		m_streamIn.read( size );

		bool result;
		m_streamIn.read( result );

		printf("Connection::handleReadConnect size - %d, result - %d\n"
			, size
			, (int)result
			);

		if( result == true )
		{
			_response( ECS_SUCCESSFUL, m_streamIn, size );
		}
		else
		{
			this->close();
			_response( ECS_FAILED, m_streamIn, size );
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void Connection::handleReadBodySize( const boost::system::error_code & _ec, std::size_t * _size )
	{
		if( _ec )
		{
			printf("Connection::handleReadBodySize ec: %s\n"
				, _ec.message().c_str() 
				);

			return;
		}

		std::size_t blob_size = *_size - sizeof(std::size_t);

		AxeUtil::Archive::value_type * blob = m_streamIn.keepBuffer( blob_size );

		m_socket->read( blob, blob_size
			, boost::bind( &Connection::handleReadBody, handlePtr(this), boost::asio::placeholders::error )
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Connection::handleReadBody( const boost::system::error_code & _ec )
	{
		if( _ec )
		{
			printf("Connection::handleReadBody ec: %s\n"
				, _ec.message().c_str() 
				);

			return;
		}

		m_streamIn.begin();

		std::size_t size;
		m_streamIn.read( size );

		this->dispatchMessage( m_streamIn, size );
		this->run();
	}
}
