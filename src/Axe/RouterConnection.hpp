#	pragma once

#	include "AdapterConnection.hpp"
#	include "ConnectionCache.hpp"

namespace Axe
{
	typedef AxeHandle<class Client> ClientPtr;

	class RouterConnection
		: public AdapterConnection
		, public ConnectionProvider
	{
	public:
		RouterConnection( boost::asio::io_service & _service );

	public:
		void createSession( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _login, const std::string & _password, const ClientPtr & _client );

	protected:
		ConnectionPtr createConnection( std::size_t _endpointId ) override;

	protected:
		ConnectionCachePtr m_connectionCache;
	};

	typedef AxeHandle<RouterConnection> RouterConnectionPtr;
}