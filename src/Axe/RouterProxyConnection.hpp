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
		RouterProxyConnection( const RouterConnectionPtr & _base, std::size_t _adapterId );

	public:
		ArchiveInvocation & beginMessage( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response ) override;

	protected:
		void connectionSuccessful( ArchiveDispatcher & _ar, std::size_t _size ) override;
		void connectionFailed( ArchiveDispatcher & _ar, std::size_t _size ) override;
		void dispatchMessage( ArchiveDispatcher & _ar, std::size_t _size ) override;

	protected:
		RouterConnectionPtr m_base;
	};

	typedef AxeHandle<RouterProxyConnection> RouterProxyConnectionPtr;
}