#	include "pch.hpp"

#	include "Invocation.hpp"

#	include "ArchiveWrite.hpp"
#	include "ArchiveRead.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Invocation::Invocation( boost::asio::io_service & _service, std::size_t _endpointId )
		: Dispatcher(_service)
		, Connection(_endpointId)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Invocation::connect( const boost::asio::ip::tcp::endpoint & _endpoint )
	{
		m_socket.async_connect( _endpoint
			, boost::bind( &Session::handleConnect, this, boost::asio::placeholders::error ) 
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Invocation::handleConnect( const boost::system::error_code & _ec )
	{
		std::size_t * size = m_streamIn.keep<std::size_t>();

		boost::asio::async_read( m_socket
			, boost::asio::buffer( size, sizeof(std::size_t) )
			, boost::bind( &Dispatcher::handleReadCondition, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, sizeof(std::size_t) )
			, boost::bind( &Session::handleReadConnectSize, this, boost::asio::placeholders::error, size )
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Invocation::handleReadConnectSize( const boost::system::error_code & _ec, std::size_t * _size )
	{
		std::size_t size_blob = *_size - sizeof(std::size_t);

		Archive::value_type * blob = m_streamIn.keepBuffer( size_blob );

		boost::asio::async_read( m_socket
			, boost::asio::buffer( blob, size_blob )
			, boost::bind( &Dispatcher::handleReadCondition, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, size_blob )
			, boost::bind( &Session::handleReadConnect, this, boost::asio::placeholders::error, blob )
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Invocation::handleReadConnect( const boost::system::error_code & _ec, Archive::value_type * _blob )
	{
		if( !_ec )
		{
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
				this->connectionFailed( m_streamIn, size );
				this->close();
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
}