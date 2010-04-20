#	pragma once

#	include <Axe/Connection.hpp>

namespace Axe
{
	class ServantConnection
		: public Connection
	{
	public:
		ServantConnection( const SocketPtr & _socket, const ConnectionCachePtr & _connectionCache, const std::string & _uniqueId );

	protected:
		void write( ArchiveInvocation & _ar ) const override;

	protected:
		ArchiveInvocation & beginMessage( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response ) override;

	protected:
		std::string m_uniqueId;
	};

	typedef AxeHandle<ServantConnection> ServantConnectionPtr;
}