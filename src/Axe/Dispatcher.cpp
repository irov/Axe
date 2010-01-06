#	include "pch.hpp"

#	include <Axe/Dispatcher.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Dispatcher::Dispatcher( boost::asio::io_service & _service, const ConnectionCachePtr & _connectionCache )
		: m_socket(_service)
		, m_connectionCache(_connectionCache)
		, m_streamIn(_connectionCache)
		, m_streamWrite(_connectionCache)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	boost::asio::ip::tcp::socket & Dispatcher::getSocket()
	{
		return m_socket;
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveInvocation & Dispatcher::getArchiveInvocation()
	{
		return m_streamWrite;
	}
	//////////////////////////////////////////////////////////////////////////
	void Dispatcher::run()
	{
		m_streamIn.clear();
		m_streamIn.begin();

		std::size_t * size = m_streamIn.keep<std::size_t>();

		boost::asio::async_read( m_socket
			, boost::asio::buffer( size, sizeof(std::size_t) )
			, boost::bind( &Dispatcher::handleReadCondition, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, sizeof(std::size_t) )
			, boost::bind( &Dispatcher::handleReadBodySize, handlePtr(this), boost::asio::placeholders::error, size )
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Dispatcher::close()
	{
		m_socket.close();
	}
	//////////////////////////////////////////////////////////////////////////
	void Dispatcher::process()
	{
		if( m_archiveSend.empty() )
		{
			m_streamWrite.swap( m_archiveSend );

			this->processArchive( m_archiveSend );
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void Dispatcher::processArchive( const AxeUtil::Archive & _ar )
	{
		std::size_t size_ar = _ar.size();

		boost::asio::async_write( m_socket
			, boost::asio::buffer( _ar, size_ar )
			, boost::bind( &Dispatcher::handleWriteStream, handlePtr(this), boost::asio::placeholders::error )
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Dispatcher::handleWriteStream( const boost::system::error_code & _ec )
	{
		if( _ec )
		{
			printf("Dispatcher::handleWriteStream ec: %s\n"
				, _ec.message().c_str() 
				);

			return;
		}
		
		m_archiveSend.clear();

		if( m_streamWrite.empty() == false )
		{
			this->process();
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void Dispatcher::handleReadBodySize( const boost::system::error_code & _ec, std::size_t * _size )
	{
		if( _ec )
		{
			printf("Dispatcher::handleReadBodySize ec: %s\n"
				, _ec.message().c_str() 
				);

			return;
		}

		std::size_t size_blob = *_size - sizeof(std::size_t);

		AxeUtil::Archive::value_type * blob = m_streamIn.keepBuffer( size_blob );

		boost::asio::async_read( m_socket
			, boost::asio::buffer( blob, size_blob )
			, boost::bind( &Dispatcher::handleReadCondition, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, size_blob )
			, boost::bind( &Dispatcher::handleReadBody, handlePtr(this), boost::asio::placeholders::error )
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Dispatcher::handleReadBody( const boost::system::error_code & _ec )
	{
		if( _ec )
		{
			printf("Dispatcher::handleReadBody ec: %s\n"
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
	//////////////////////////////////////////////////////////////////////////
	bool Dispatcher::handleReadCondition( const boost::system::error_code & _ec, std::size_t _read, std::size_t _wait )
	{
		return ( _read >= _wait );
	}

}