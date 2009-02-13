#	pragma once

#	include "Service.hpp"
#	include "Servant.hpp"

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
		std::size_t addServant( const ServantPtr & _servant );

	public:
		void setEndpointId( std::size_t _endpointId );

		void refreshServantEndpoint( std::size_t _endpointId );

	public:
		void dispatchMethod( std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, const SessionPtr & _session );

	protected:
		typedef std::map<std::size_t, ServantPtr> TMapServants;
		TMapServants m_servants;

		std::size_t m_endpointId;

		ConnectionCachePtr m_connectionCache;
	};

	typedef AxeHandle<Host> HostPtr;
}