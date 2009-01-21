#	pragma once

#	include "AdapterConnection.hpp"

namespace Axe
{
	typedef AxeHandle<class Connection> ConnectionPtr;
	typedef AxeHandle<class RouterProxyConnection> RouterProxyConnectionPtr;
	
	class RouterConnection
		: public AdapterConnection
	{
	public:
		RouterConnection( boost::asio::io_service & _service );

	public:
		void createSession( const std::string & _login, const std::string & _password, const ClientPtr & _client );

	protected:
		const RouterProxyConnectionPtr & getConnection( std::size_t _id );

	protected:
		typedef std::map<std::size_t, RouterProxyConnectionPtr> TMapRouterConnections;
		TMapRouterConnections m_connections;
	};
}