#	pragma once

#	include <Axe/Service.hpp>
#	include <Axe/ServantProvider.hpp>

namespace Axe
{
	typedef AxeHandle<class Session> SessionPtr;
	typedef AxeHandle<class Servant> ServantPtr;
	typedef AxeHandle<class ServantProvider> ServantProviderPtr;

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
		void dispatchMethod( std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const SessionPtr & _session );

	public:
		const ConnectionCachePtr & getConnectionCahce() const;

	protected:
		ConnectionCachePtr m_connectionCache;
		ServantProviderPtr m_servantProvider;

		std::size_t m_hostId;

		typedef std::map<std::size_t, ServantPtr> TMapServants;
		TMapServants m_servants;
	};

	typedef AxeHandle<Host> HostPtr;
}