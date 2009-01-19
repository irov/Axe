#	pragma once

#	include "Host.hpp"

namespace Axe
{
	typedef AxeHandle<class AdapterSession> AdapterSessionPtr;
	typedef AxeHandle<class Connection> ConnectionPtr;
	typedef AxeHandle<class Servant> ServantPtr;

	class Adapter
		: public Host
	{
	public:
		Adapter( std::size_t _id, const boost::asio::ip::tcp::endpoint & _endpoint );

	public:
		void initialize();

	public:
		std::size_t addServant( const ServantPtr & _servant );

		void dispatchMethod( std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, const AdapterSessionPtr & _session );

	protected:
		SessionPtr makeSession() override;

	protected:
		std::size_t m_id;

		typedef std::map<std::size_t, ServantPtr> TMapServants;
		TMapServants m_servants;
	};

	typedef AxeHandle<Adapter> AdapterPtr;
}