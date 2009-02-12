#	pragma once

#	include "Adapter.hpp"

#	include "AxeProtocols/Player.hpp"

namespace Axe
{
	class Grid
		: public Adapter
	{	
	public:
		Grid( const boost::asio::ip::tcp::endpoint & _endpoint );

	public:
		void initialize();

	protected:
		SessionPtr makeSession() override;

	protected:
		typedef std::map<std::string, std::size_t> TMapAdapterIDs;
	};

	typedef AxeHandle<Grid> GridPtr;
}
