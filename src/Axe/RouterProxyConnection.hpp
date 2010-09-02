#	pragma once

#	include <Axe/RouterConnection.hpp>
#	include <Axe/Connection.hpp>

namespace Axe
{
	class ArchiveInvocation;

	class RouterProxyConnection
		: public Connection
	{
	public:
		RouterProxyConnection( const RouterConnectionPtr & _base );

	public:
		ArchiveInvocation & beginMessage( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response ) override;

	protected:
		void dispatchMessage( ArchiveDispatcher & _ar, std::size_t _size ) override;

	protected:
		void write( ArchiveInvocation & _ar ) const override;

	protected:
		RouterConnectionPtr m_base;
	};

	typedef AxeHandle<RouterProxyConnection> RouterProxyConnectionPtr;
}