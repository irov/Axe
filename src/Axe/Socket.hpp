#	pragma once

#	include <AxeUtil/Shared.hpp>

namespace Axe
{
	class SocketConnectResponse
		: virtual public AxeUtil::Shared
	{
	public:
		virtual void onConnect( const boost::system::error_code & _ec ) = 0;
	};

	typedef AxeHandle<SocketConnectResponse> SocketConnectResponsePtr;

	class SocketAcceptResponse
		: virtual public AxeUtil::Shared
	{
	public:
		virtual void onAccept( const boost::system::error_code & _ec ) = 0;
	};

	typedef AxeHandle<SocketAcceptResponse> SocketAcceptResponsePtr;

	class Socket
		: virtual public AxeUtil::Shared
	{
	public:
		Socket( boost::asio::io_service & _service );

	protected:
		void connect( const boost::asio::ip::tcp::endpoint & _endpoint, const SocketConnectResponsePtr & _response );
		void accept( boost::asio::ip::tcp::acceptor & _aceeptor, const SocketAcceptResponsePtr & _response );
		void close();

	protected:
		static bool handleReadCondition( const boost::system::error_code & _ec, std::size_t _read, std::size_t _wait );

	protected:
		boost::asio::ip::tcp::socket m_socket;
	};

	typedef AxeHandle<Socket> SocketPtr;
}