#	pragma once

#	include <AxeUtil/Shared.hpp>
#	include <AxeUtil/Archive.hpp>

namespace Axe
{
	typedef boost::function1<void, boost::system::error_code> FSocketConnectResponse;
	typedef boost::function1<void, boost::system::error_code> FSocketAcceptResponse;
	typedef boost::function2<void, boost::system::error_code, std::size_t> FSocketReadResponse;
	typedef boost::function2<void, boost::system::error_code, std::size_t> FSocketWriteResponse;

	class Socket
		: virtual public AxeUtil::Shared
	{
	public:
		Socket( boost::asio::io_service & _service );

	public:
		void connect( const boost::asio::ip::tcp::endpoint & _endpoint, const FSocketConnectResponse & _response );
		void accept( boost::asio::ip::tcp::acceptor & _aceeptor, const FSocketAcceptResponse & _response );
		void close();

	public:
		bool is_open() const;

	public:
		void read( void * _buffer, std::size_t _size, const FSocketReadResponse & _response );
		void write( void * _buffer, std::size_t _size, const FSocketWriteResponse & _response );

		void read_arhive( const AxeUtil::Archive & _ar, const FSocketReadResponse & _response );
		void write_arhive( const AxeUtil::Archive & _ar, const FSocketWriteResponse & _response );

	protected:
		boost::asio::ip::tcp::socket m_socket;
	};

	typedef AxeHandle<Socket> SocketPtr;
}