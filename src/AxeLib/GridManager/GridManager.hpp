#	pragma once

#	include <AxeProtocols/GridManager.hpp>

namespace AxeLib
{
	using namespace Axe;

	class GridManager
		: public Servant_GridManager
	{
	public:
		GridManager();

	public:
		void addAdapter_async( const Bellhop_GridManager_addAdapterPtr & _cb, const std::string & _name, const std::string & _endpoint ) override;
		void getAdapterEndpoint_async( const Bellhop_GridManager_getAdapterEndpointPtr & _cb, std::size_t _hostId ) override;

		void addUnique_async( const Bellhop_GridManager_addUniquePtr & _cb, const std::string & _name, const ProxyPtr & _unique ) override;
		void getUnique_async( const Bellhop_GridManager_getUniquePtr & _cb, const std::string & _name ) override;		

		void getServantTypeId_async( const Bellhop_GridManager_getServantTypeIdPtr & _cb, const std::string & _type );
	};

	typedef AxeHandle<GridManager> GridManagerPtr;
}
