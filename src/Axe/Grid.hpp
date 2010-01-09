#	pragma once

#	include <Axe/Host.hpp>

namespace Axe
{
	typedef AxeHandle<class Servant_GridManager> Servant_GridManagerPtr;
	typedef AxeHandle<class Proxy_GridManager> Proxy_GridManagerPtr;

	class Grid
		: public Host
	{	
	public:
		Grid( const CommunicatorPtr & _communicator, const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name );

	public:
		void start();

	public:
		const Proxy_GridManagerPtr & addGridManager( const Servant_GridManagerPtr & _servant );
		const Proxy_GridManagerPtr & getGridManager() const;

	protected:
		SessionPtr makeSession() override;

	protected:
		Proxy_GridManagerPtr m_gridManager;
	};

	typedef AxeHandle<Grid> GridPtr;
}
