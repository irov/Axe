#	pragma once

#	include "AxeProtocols/Player.hpp"

namespace Axe
{
	class GridManager
		: public Servant_GridManager
	{
	public:
		void addAdapter( const Bellhop_GridManager_addAdapterPtr & _cb, const std::string & _name ) override;

		void addUnique( const Bellhop_GridManager_addUniquePtr & _cb, const std::string & _name, const Proxy_UniquePtr & _unique ) override;
		void getUnique( const Bellhop_GridManager_getUniquePtr & _cb, const std::string & _name ) override;		

	protected:
		typedef std::map<std::string, Proxy_UniquePtr> TMapUniques;
		TMapUniques m_uniques;
	};
}
