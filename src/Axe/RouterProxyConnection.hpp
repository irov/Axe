#	pragma once

#	include <Axe/RouterConnection.hpp>

namespace Axe
{
	class ArchiveWrite;

	class RouterProxyConnection
		: public Connection
	{
	public:
		RouterProxyConnection( const RouterConnectionPtr & _base, std::size_t _hostId );

	public:
		ArchiveWrite & beginMessage( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response ) override;

		void processMessage() override;

	protected:
		RouterConnectionPtr m_base;
	};

	typedef AxeHandle<RouterProxyConnection> RouterProxyConnectionPtr;
}