#	pragma once

#	include "Service.hpp"
#	include "Servant.hpp"
#	include "Proxy.hpp"

#	include "ConnectionCache.hpp"

namespace Axe
{
	typedef AxeHandle<class Session> SessionPtr;
	typedef AxeHandle<class Connection> ConnectionPtr;

	class Host
		: public Service
		, public ConnectionProvider
	{
	public:
		Host( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name );

	public:
		ProxyPtr addServant( const ServantPtr & _servant );

	public:
		void setHostId( std::size_t _hostId );

		void refreshServantEndpoint( std::size_t _hostId );

	public:
		void dispatchMethod( std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, const SessionPtr & _session );

	protected:
		typedef std::map<std::size_t, ServantPtr> TMapServants;
		TMapServants m_servants;

		std::size_t m_hostId;

		ConnectionCachePtr m_connectionCache;
	};

	typedef AxeHandle<Host> HostPtr;
}