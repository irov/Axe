#	include "pch.hpp"

#	include "Session.hpp"
#	include "Exception.hpp"

#	include "ArchiveInvocation.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Session::Session( const SocketPtr & _socket, const ConnectionCachePtr & _connectionCache )
		: Connection(_socket, _connectionCache)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Session::accept()
	{
		m_streamIn.clear();
		m_streamIn.begin();

		std::size_t * size = m_streamIn.keep<std::size_t>();

		//boost::asio::async_read( m_socket
		//	, boost::asio::buffer( size, sizeof(std::size_t) )
		//	, boost::bind( &Dispatcher::handleReadCondition, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, sizeof(std::size_t) )
		//	, boost::bind( &Session::handleReadPermissionSize, handlePtr(this), boost::asio::placeholders::error, size )
		//	);

		m_socket->read( size, sizeof(std::size_t)
			, boost::bind( &Session::handleReadPermissionSize, handlePtr(this), boost::asio::placeholders::error, size )
			);
	}
	////////////////////////////////////////////////////////////////////////////
	ArchiveInvocation & Session::beginConnect( bool _successful )
	{
		m_streamOut.begin();

		m_streamOut << _successful;

		return m_streamOut;
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveInvocation & Session::beginResponse( std::size_t _responseId )
	{
		m_streamOut.begin();
		m_streamOut.writeSize( _responseId );
		m_streamOut.writePOD( true );

		return m_streamOut;
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveInvocation & Session::beginException( std::size_t _responseId )
	{
		m_streamOut.begin();
		m_streamOut.writeSize( _responseId );
		m_streamOut.writePOD( false );

		return m_streamOut;
	}
	//////////////////////////////////////////////////////////////////////////
	void Session::processException( std::size_t _requestId, std::size_t _exceptionId, const Exception & _ex )
	{
		ArchiveInvocation & ar = this->beginException( _requestId );

		ar.writeSize( _exceptionId );
		_ex.write( ar );

		this->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Session::handleReadPermissionSize( const boost::system::error_code & _ec, std::size_t * _size )
	{
		if( _ec )
		{
			printf("Session::handleReadPermissionSize ec: %s\n", _ec.message().c_str() );
			return;
		}

		std::size_t blob_size = *_size - sizeof(std::size_t);
		
		if( blob_size == 0 )
		{
			boost::system::error_code ec;
			this->handleReadPermission( ec );
			return;
		}

		AxeUtil::Archive::value_type * blob = m_streamIn.keepBuffer( blob_size );

		//boost::asio::async_read( m_socket
		//	, boost::asio::buffer( blob, size_blob )
		//	, boost::bind( &Dispatcher::handleReadCondition, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, size_blob )
		//	, boost::bind( &Session::handleReadPermission, handlePtr(this), boost::asio::placeholders::error )
		//	);

		m_socket->read( blob, blob_size
			, boost::bind( &Session::handleReadPermission, handlePtr(this), boost::asio::placeholders::error )
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Session::handleReadPermission( const boost::system::error_code & _ec )
	{
		if( _ec )
		{
			printf("Session::handleReadPermission ec: %s\n", _ec.message().c_str() );
			return;
		}

		m_streamIn.begin();

		std::size_t size;
		m_streamIn.read( size );

		this->permissionVerify( m_streamIn, size );
	}
	//////////////////////////////////////////////////////////////////////////
	void Session::connectionSuccessful( ArchiveDispatcher & _ar, std::size_t _size )
	{
		//Empty
	}
	//////////////////////////////////////////////////////////////////////////
	void Session::connectionFailed( ArchiveDispatcher & _ar, std::size_t _size )
	{
		//Empty
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveInvocation & Session::beginMessage( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response )
	{
		return m_streamOut;
	}
}