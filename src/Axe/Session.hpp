#	pragma once

#	include "Dispatcher.hpp"

namespace Axe
{
	class Session
		: public Dispatcher
	{
	public:
		Session( boost::asio::io_service & _service, const ConnectionCachePtr & _connectionCache );

	public:
		void accept();

	public:
		ArchiveWrite & beginConnect( bool _successful );
		ArchiveWrite & beginResponse();
		ArchiveWrite & beginException();

	protected:
		void handleReadPermissionSize( const boost::system::error_code & _ec, std::size_t * _size );
		void handleReadPermission( const boost::system::error_code & _ec );

	public:
		virtual void permissionVerify( ArchiveRead & _ar, std::size_t _size ) = 0;
	};

	typedef AxeHandle<Session> SessionPtr;
}