#	pragma once

#	include <Axe/Connection.hpp>

namespace Axe
{
	class Exception;

	class Session
		: public Connection
	{
	public:
		Session( const SocketPtr & _socket, const ConnectionCachePtr & _connectionCache );

	public:
		void accept();

	public:
		ArchiveInvocation & beginConnect( bool _successful );
		ArchiveInvocation & beginResponse( std::size_t _responseId );
		ArchiveInvocation & beginException( std::size_t _responseId );

	public:
		void processException( std::size_t _requestId, std::size_t _exceptionId, const Exception & _ex );

	protected:
		void handleReadPermissionSize( const boost::system::error_code & _ec, std::size_t * _size );
		void handleReadPermission( const boost::system::error_code & _ec );

	public:
		virtual void permissionVerify( ArchiveDispatcher & _ar, std::size_t _size ) = 0;

	protected:
		void connectionSuccessful( ArchiveDispatcher & _ar, std::size_t _size ) override;
		void connectionFailed( ArchiveDispatcher & _ar, std::size_t _size ) override;
		ArchiveInvocation & beginMessage( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response ) override;
	};

	typedef AxeHandle<Session> SessionPtr;
}