#	pragma once

#	include "Host.hpp"

#	include "Communicator.hpp"

#	include "AxeProtocols/Player.hpp"

namespace Axe
{
	typedef AxeHandle<class AdapterSession> AdapterSessionPtr;
	typedef AxeHandle<class Connection> ConnectionPtr;

	class Adapter
		: public Host		
	{
	public:
		Adapter( const CommunicatorPtr & _communicator, const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name, std::size_t _adapterId );

	public:
		void addUnique( const std::string & _name, const Servant_UniquePtr & _unique );

		void addServant( const ServantPtr & _servant ); 

	protected:
		SessionPtr makeSession() override;

	protected:
		CommunicatorPtr m_communicator;

		std::size_t m_adapterId;
	};

	typedef AxeHandle<Adapter> AdapterPtr;
}