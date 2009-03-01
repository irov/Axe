#	pragma once

#	include "Host.hpp"

#	include "AxeProtocols/Player.hpp"

namespace Axe
{
	class Grid
		: public Host
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
		ConnectionPtr createConnection( std::size_t _hostId ) override;

	protected:
		Proxy_GridManagerPtr m_gridManager;
	};

	typedef AxeHandle<Grid> GridPtr;
}
