#	include "pch.hpp"

#	include "Session.hpp"

#	include "ArchiveWrite.hpp"
#	include "ArchiveRead.hpp"

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
			, boost::bind( &Session::handleReadPermissionSize, intrusivePtr(this), boost::asio::placeholders::error, size )
			);
	}
	////////////////////////////////////////////////////////////////////////////
	ArchiveWrite & Session::beginConnect( bool _successful )
	{
		m_streamWrite.begin();

		m_streamWrite.write( _successful );

		return m_streamWrite;
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveWrite & Session::beginResponse( std::size_t _responseId )
	{
		m_streamWrite.begin();

		m_streamWrite.writePOD( true );

		m_streamWrite.writeSize( _responseId );

		return m_streamWrite;
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveWrite & Session::beginException( std::size_t _responseId )
	{
		m_streamWrite.begin();

		m_streamWrite.writePOD( false );

		m_streamWrite.writeSize( _responseId );

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
		
		if( size_blob )
		{
			Archive::value_type * blob = m_streamIn.keepBuffer( size_blob );

			boost::asio::async_read( m_socket
				, boost::asio::buffer( blob, size_blob )
				, boost::bind( &Dispatcher::handleReadCondition, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, size_blob )
				, boost::bind( &Session::handleReadPermission, intrusivePtr(this), boost::asio::placeholders::error )
				);
		}
		else
		{
			boost::system::error_code ec;
			this->handleReadPermission( ec );
		}
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