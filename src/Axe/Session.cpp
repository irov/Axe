#	include "pch.hpp"

#	include <Axe/Session.hpp>

#	include <Axe/ArchiveInvocation.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Session::Session( boost::asio::io_service & _service, const ConnectionCachePtr & _connectionCache )
		: Dispatcher(_service, _connectionCache)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Session::accept()
	{
		m_streamIn.clear();
		m_streamIn.begin();

		std::size_t * size = m_streamIn.keep<std::size_t>();

		boost::asio::async_read( m_socket
			, boost::asio::buffer( size, sizeof(std::size_t) )
			, boost::bind( &Dispatcher::handleReadCondition, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, sizeof(std::size_t) )
			, boost::bind( &Session::handleReadPermissionSize, handlePtr(this), boost::asio::placeholders::error, size )
			);
	}
	////////////////////////////////////////////////////////////////////////////
	ArchiveInvocation & Session::beginConnect( bool _successful )
	{
		m_streamWrite.begin();

		m_streamWrite << _successful;

		return m_streamWrite;
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveInvocation & Session::beginResponse( std::size_t _responseId )
	{
		m_streamWrite.begin();
		m_streamWrite.writeSize( _responseId );
		m_streamWrite.writePOD( true );

		return m_streamWrite;
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveInvocation & Session::beginException( std::size_t _responseId )
	{
		m_streamWrite.begin();
		m_streamWrite.writeSize( _responseId );
		m_streamWrite.writePOD( false );

		return m_streamWrite;
	}
	//////////////////////////////////////////////////////////////////////////
	void Session::handleReadPermissionSize( const boost::system::error_code & _ec, std::size_t * _size )
	{
		if( _ec )
		{
			printf("Session::handleReadPermissionSize ec: %s\n", _ec.message().c_str() );
			return;
		}

		std::size_t size_blob = *_size - sizeof(std::size_t);
		
		if( size_blob == 0 )
		{
			boost::system::error_code ec;
			this->handleReadPermission( ec );
			return;
		}

		AxeUtil::Archive::value_type * blob = m_streamIn.keepBuffer( size_blob );

		boost::asio::async_read( m_socket
			, boost::asio::buffer( blob, size_blob )
			, boost::bind( &Dispatcher::handleReadCondition, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, size_blob )
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
}