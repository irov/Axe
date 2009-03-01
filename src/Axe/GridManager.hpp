#	pragma once

#	include "AxeProtocols/Player.hpp"

namespace Axe
{
	class GridManager
		: public Servant_GridManager
	{
	public:
		GridManager();

	public:
		void addAdapter( const Bellhop_GridManager_addAdapterPtr & _cb, const std::string & _name, const std::string & _endpoint ) override;
		void getAdapterEndpoint( const Bellhop_GridManager_getAdapterEndpointPtr & _cb, std::size_t _hostId ) override;

		void addUnique( const Bellhop_GridManager_addUniquePtr & _cb, const std::string & _name, const Proxy_UniquePtr & _unique ) override;
		void getUnique( const Bellhop_GridManager_getUniquePtr & _cb, const std::string & _name ) override;		

	protected:
		typedef std::map<std::string, Proxy_UniquePtr> TMapUniques;
		TMapUniques m_uniques;

		typedef std::map<std::size_t, std::string> TMapEndpoints;
		TMapEndpoints m_endpoints;
	};

	typedef AxeHandle<GridManager> GridManagerPtr;
}
