#	pragma once

#	include "Host.hpp"

#	include "AxeProtocols/Player.hpp"

namespace Axe
{
	class Grid
		: public Service
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
		Proxy_GridManagerPtr m_gridManager;
	};

	typedef AxeHandle<Grid> GridPtr;
}
