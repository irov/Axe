#	pragma once

#	include "Adapter.hpp"

namespace Axe
{
	class Grid
		: public Adapter
	{	
	public:
		Grid( const boost::asio::ip::tcp::endpoint & _endpoint );

	public:
		void initialize();

	public:
		std::size_t addAdapter( const std::string & _adapter ); 

	protected:
		SessionPtr makeSession() override;

	protected:
		typedef std::map<std::string, std::size_t> TMapAdapterIDs;

		TMapAdapterIDs m_adapterIds;
		std::size_t m_enumeratorID;
	};

	typedef AxeHandle<Grid> GridPtr;
}
