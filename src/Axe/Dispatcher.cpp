#	include "pch.hpp"

#	include "Dispatcher.hpp"

#	include "ArchiveWrite.hpp"
#	include "ArchiveRead.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Dispatcher::Dispatcher( boost::asio::io_service & _service )
		: m_socket(_service)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	boost::asio::ip::tcp::socket & Dispatcher::getSocket()
	{
		return m_socket;
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveRead & Dispatcher::getArchiveRead()
	{
		return m_streamIn;
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveWrite & Dispatcher::getArchiveWrite()
	{
		return m_streamWrite;
	}
	//////////////////////////////////////////////////////////////////////////
	void Dispatcher::run()
	{
		std::size_t * size = m_streamIn.keep<std::size_t>();

		boost::asio::async_read( m_socket
			, boost::asio::buffer( size, sizeof(std::size_t) )
			, boost::bind( &Dispatcher::handleReadCondition, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, sizeof(std::size_t) )
			, boost::bind( &Dispatcher::handleReadBodySize, this, boost::asio::placeholders::error, size )
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Dispatcher::close()
	{
		
	}
	//////////////////////////////////////////////////////////////////////////
	void Dispatcher::process()
	{
		if( m_streamSend.empty() )
		{
			std::swap( m_streamWrite, m_streamSend );

			const Archive & blob = m_streamSend.getArchive();

			boost::asio::async_write( m_socket
				, boost::asio::buffer( blob )
				, boost::bind( &Dispatcher::handleWriteStream, this, boost::asio::placeholders::error )
				);
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void Dispatcher::handleWriteStream( const boost::system::error_code & _ec )
	{
		m_streamSend.clear();

		if( m_streamWrite.empty() == false )
		{
			this->process();
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void Dispatcher::handleReadBodySize( const boost::system::error_code & _ec, std::size_t * _size )
	{
		std::size_t size_blob = *_size - sizeof(std::size_t);

		Archive::value_type * blob = m_streamIn.keepBuffer( size_blob );

		boost::asio::async_read( m_socket
			, boost::asio::buffer( blob, size_blob )
			, boost::bind( &Dispatcher::handleReadCondition, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, size_blob )
			, boost::bind( &Dispatcher::handleReadBody, this, boost::asio::placeholders::error, blob )
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Dispatcher::handleReadBody( const boost::system::error_code & _ec, Archive::value_type * _blob )
	{
		if( !_ec )
		{
			m_streamIn.begin();

			std::size_t size;
			m_streamIn.read( size );

			this->dispatchMessage( m_streamIn, size );
			this->run();
		}
	}
	//////////////////////////////////////////////////////////////////////////
	bool Dispatcher::handleReadCondition( const boost::system::error_code & _ec, std::size_t _read, std::size_t _wait )
	{
		return ( _read >= _wait );
	}

}