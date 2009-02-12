#	pragma once

#	include "AxeProtocols/Player.hpp"

namespace Axe
{
	class GridManager
		: public Servant_GridManager
	{
	public:
		void addAdapter( const Bellhop_GridManager_addAdapterPtr & _cb, const std::string & _name ) override;
	};
}
