#	pragma once

#	include "AdapterConnection.hpp"

namespace Axe
{
	typedef AxeHandle<class RouterProxyConnection> RouterProxyConnectionPtr;

	class RouterConnection
		: public AdapterConnection
	{
	public:
		RouterConnection( boost::asio::io_service & _service );

	public:
		void dispatchMessage( std::size_t _size ) override;

	protected:
		const ConnectionPtr & getConnection( std::size_t _id );

	protected:
		typedef std::map<std::size_t, RouterProxyConnectionPtr> TMapRouterConnections;
		TMapRouterConnections m_connections;
	};
}