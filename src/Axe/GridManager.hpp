#	pragma once

#	include "AxeProtocols/Player.hpp"

namespace Axe
{
	class GridManager
		: public Servant_GridManager
	{
	public:
		void addAdapter( const Bellhop_GridManager_addAdapterPtr & _cb, const std::string & _name ) override;

		void getSessionManager( const Bellhop_GridManager_getSessionManagerPtr & _cb ) override;
		void setSessionManager( const Bellhop_GridManager_setSessionManagerPtr & _cb, const Proxy_SessionManagerPtr & _sessionManager ) override;

	protected:
		Proxy_SessionManagerPtr m_sessionManager;
	};
}
