#	pragma once

#	include "Host.hpp"

#	include "ConnectionCache.hpp"

namespace Axe
{
	typedef AxeHandle<class AdapterSession> AdapterSessionPtr;
	typedef AxeHandle<class Connection> ConnectionPtr;
	typedef AxeHandle<class Servant> ServantPtr;

	class Adapter
		: public Host
		, public ConnectionProvider
	{
	public:
		Adapter( const std::string & _name, const boost::asio::ip::tcp::endpoint & _endpoint );

	public:
		void initialize();

	public:
		std::size_t addServant( const ServantPtr & _servant );

		void dispatchMethod( std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, const AdapterSessionPtr & _session );

	protected:
		SessionPtr makeSession() override;

	protected:
		ConnectionPtr createConnection( std::size_t _endpointId ) override;

	protected:
		std::string m_name;
		std::size_t m_id;

		typedef std::map<std::size_t, ServantPtr> TMapServants;
		TMapServants m_servants;

		ConnectionCachePtr m_connectionCache;
	};

	typedef AxeHandle<Adapter> AdapterPtr;
}