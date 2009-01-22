#	pragma once

#	include "RouterConnection.hpp"

namespace Axe
{
	class ArchiveWrite;

	class RouterProxyConnection
		: public Connection
	{
	public:
		RouterProxyConnection( const RouterConnectionPtr & _base, std::size_t _endpointId );

	public:
		ArchiveWrite & beginMessage( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response ) override;

		void process() override;

	protected:
		RouterConnectionPtr m_base;
	};

	typedef AxeHandle<RouterProxyConnection> RouterProxyConnectionPtr;
}