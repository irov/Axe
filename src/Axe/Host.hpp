#	pragma once

#	include <Axe/Service.hpp>
#	include <Axe/Proxy.hpp>

namespace Axe
{
	typedef AxeHandle<class Session> SessionPtr;
	typedef AxeHandle<class Servant> ServantPtr;

	class Host
		: public Service
	{
	public:
		Host( boost::asio::io_service & _service, const ConnectionCachePtr & _connectionCache, const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name, std::size_t _hostId );

	public:
		ProxyPtr addServant( std::size_t _servantId, const ServantPtr & _servant );

	public:
		void setHostId( std::size_t _hostId );
		std::size_t getHostId() const;

		void refreshServantEndpoint( std::size_t _hostId );

	public:
		void dispatchMethod( std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, const SessionPtr & _session );

	protected:
		ConnectionCachePtr m_connectionCache;

		std::size_t m_hostId;

		typedef std::map<std::size_t, ServantPtr> TMapServants;
		TMapServants m_servants;		
	};

	typedef AxeHandle<Host> HostPtr;
}