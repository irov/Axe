#	pragma once

#	include "Dispatcher.hpp"

namespace Axe
{
	class Session
		: public Dispatcher
	{
	public:
		Session( boost::asio::io_service & _service );

	public:
		void accept();
		//void connect( const boost::asio::ip::tcp::endpoint & _endpoint );
		//void process();

	public:
		ArchiveWrite & beginResponse();

	//protected:
	//	void handleConnect( const boost::system::error_code & _ec );

	protected:
		void handleReadPermissionSize( const boost::system::error_code & _ec, std::size_t * _size );
		void handleReadPermission( const boost::system::error_code & _ec, Archive::value_type * _blob );

	public:
		virtual void permissionVerify( ArchiveRead & _ar, std::size_t _size ) = 0;
	};

	typedef AxeHandle<Session> SessionPtr;
}