#	include "pch.hpp"

#	include "Session.hpp"

#	include "ArchiveWrite.hpp"
#	include "ArchiveRead.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Session::Session( boost::asio::io_service & _service )
		: Dispatcher(_service)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Session::accept()
	{
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
	ArchiveWrite & Session::beginResponse()
	{
		m_streamWrite.begin();

		return m_streamWrite;
	}
	//////////////////////////////////////////////////////////////////////////
	void Session::handleReadPermissionSize( const boost::system::error_code & _ec, std::size_t * _size )
	{
		std::size_t size_blob = *_size - sizeof(std::size_t);

		Archive::value_type * blob = m_streamIn.keepBuffer( size_blob );

		boost::asio::async_read( m_socket
			, boost::asio::buffer( blob, size_blob )
			, boost::bind( &Dispatcher::handleReadCondition, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, size_blob )
			, boost::bind( &Session::handleReadPermission, intrusivePtr(this), boost::asio::placeholders::error, blob )
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Session::handleReadPermission( const boost::system::error_code & _ec, Archive::value_type * _blob )
	{
		if( !_ec )
		{
			m_streamIn.begin();

			std::size_t size;
			m_streamIn.read( size );

			this->permissionVerify( m_streamIn, size );
		}
	}
	//////////////////////////////////////////////////////////////////////////
}