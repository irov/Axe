#	include "pch.hpp"

#	include "Connection.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Connection::Connection( const SocketPtr & _socket, const ConnectionCachePtr & _connectionCache )
		: m_socket(_socket)
		, m_permission(_connectionCache)
		, m_streamIn(_connectionCache)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	namespace
	{
		class ConnectionSocketConnectResponse
			: public SocketConnectResponse
		{
		public:
			ConnectionSocketConnectResponse()
			{
			}

		protected:
			void onConnect( const boost::system::error_code & _ec ) override
			{
				if( _ec )
				{
					printf("Connection::handleConnect ec: %s\n"
						, _ec.message().c_str() 
						);
					return;
				}

				printf("Connection::handleConnect successful\n"
					);

				//if( m_permission.empty() == false )
				//{
				//	printf("Connection::handleConnect send permission \n"
				//		);

				//	const AxeUtil::Archive & ar = m_permission.getArchive();

				//	this->processArchive( ar );
				//}

				std::size_t * size = m_streamIn.keep<std::size_t>();

				boost::asio::async_read( m_socket
					, boost::asio::buffer( size, sizeof(std::size_t) )
					, boost::bind( &Socket::handleReadCondition, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, sizeof(std::size_t) )
					, boost::bind( &ConnectionSocketConnectResponse::handleReadConnectSize, handlePtr(this), boost::asio::placeholders::error, size )
					);
			}

			void handleReadConnectSize( const boost::system::error_code & _ec, std::size_t * _size )
			{
				if( _ec )
				{
					printf("Connection::handleReadConnectSize ec: %s\n"
						, _ec.message().c_str() 
						);

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

		//protected:
		//	AxeUtil::Archive m_permission
		};
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveInvocation & Connection::connect( const boost::asio::ip::tcp::endpoint & _endpoint )
	{
		m_permission.begin();

		printf("Connection::connect endpoint %s\n"
			, _endpoint.address().to_string().c_str()
			);

		m_socket.async_connect( _endpoint
			, boost::bind( &Connection::handleConnect, handlePtr(this), boost::asio::placeholders::error ) 
			);

		m_socket->connect( _endpoint,  )

		return m_permission;
	}
	//////////////////////////////////////////////////////////////////////////
	void Connection::close()
	{
		m_socket.close();
	}
	//////////////////////////////////////////////////////////////////////////
	void Connection::processMessage()
	{
		printf("Connection::processMessage adapter\n");

		if( m_socket.is_open() == false )
		{
			printf("Connection::processMessage m_socket is closed, opening\n"
				);

			this->reconnect();
		}
		else
		{
			printf("Connection::processMessage process\n"
				);

			this->process();
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void Connection::handleConnect( const boost::system::error_code & _ec )
	{
		if( _ec )
		{
			printf("Connection::handleConnect ec: %s\n"
				, _ec.message().c_str() 
				);
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

		boost::asio::async_read( m_socket
			, boost::asio::buffer( size, sizeof(std::size_t) )
			, boost::bind( &Connection::handleReadCondition, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, sizeof(std::size_t) )
			, boost::bind( &Connection::handleReadConnectSize, handlePtr(this), boost::asio::placeholders::error, size )
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Connection::handleReadConnectSize( const boost::system::error_code & _ec, std::size_t * _size )
	{
		if( _ec )
		{
			printf("Connection::handleReadConnectSize ec: %s\n"
				, _ec.message().c_str() 
				);

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
	void Connection::handleReadConnect( const boost::system::error_code & _ec, AxeUtil::Archive::value_type * _blob )
	{
		if( _ec )
		{
			printf("Connection::handleReadConnect ec: %s\n", _ec.message().c_str() );
			return;
		}

		m_streamIn.begin();

		std::size_t size;
		m_streamIn.read( size );

		bool result;
		m_streamIn.read( result );

		printf("Connection::handleReadConnect adapter - %d size - %d, result - %d\n"
			, m_adapterId
			, size
			, (int)result
			);

		if( result == true )
		{
			this->connectionSuccessful( m_streamIn, size );
		}
		else
		{
			this->close();
			this->connectionFailed( m_streamIn, size );
		}
	}
}
