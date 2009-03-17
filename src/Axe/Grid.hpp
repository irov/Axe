#	pragma once

#	include "Host.hpp"

#	include "AxeProtocols/Player.hpp"

namespace Axe
{
	class Grid
		: public Host
		, public ConnectionProvider
	{	
	public:
		Grid( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name );

	public:
		void initialize();

	public:
		const Proxy_GridManagerPtr & getGridManager() const;

	protected:
		SessionPtr makeSession() override;

	protected:
		ConnectionPtr createConnection( std::size_t _hostId, const ConnectionCachePtr & _connectionCache ) override;

	protected:
		boost::asio::io_service m_service;
		Proxy_GridManagerPtr m_gridManager;
	};

	typedef AxeHandle<Grid> GridPtr;
}
