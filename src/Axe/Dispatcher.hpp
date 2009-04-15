#	pragma once

#	include <AxeUtil/Shared.hpp>

#	include <Axe/ArchiveInvocation.hpp>
#	include <Axe/ArchiveDispatcher.hpp>

namespace Axe
{
	class Dispatcher
		: virtual public AxeUtil::Shared
	{
	public:
		Dispatcher( boost::asio::io_service & _service, const ConnectionCachePtr & _connectionCache );

	public:
		void process();

	public:
		boost::asio::ip::tcp::socket & getSocket();

		ArchiveDispatcher & getArchiveDispatcher();
		ArchiveInvocation & getArchiveInvocation();

	protected:
		void processArchive( const AxeUtil::Archive & _ar );

	public:
		void run();
		void close();

	protected:
		void handleWriteStream( const boost::system::error_code & _ec );

	protected:
		void handleReadBodySize( const boost::system::error_code & _ec, std::size_t * _size );
		void handleReadBody( const boost::system::error_code & _ec );

	public:
		virtual void dispatchMessage( ArchiveDispatcher & _ar, std::size_t _size ) = 0;

	protected:
		static bool handleReadCondition( const boost::system::error_code & _ec, std::size_t _read, std::size_t _wait );

	protected:
		ArchiveInvocation m_streamWrite;
		ArchiveInvocation m_streamSend;

		ArchiveDispatcher m_streamIn;

		ConnectionCachePtr m_connectionCache;

		boost::asio::ip::tcp::socket m_socket;
	};
}