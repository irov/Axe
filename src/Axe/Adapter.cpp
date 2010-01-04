#	include "pch.hpp"
#	include <Axe/Adapter.hpp>

#	include <Axe/Communicator.hpp>

#	include <Axe/AdapterSession.hpp>
#	include <Axe/AdapterConnection.hpp>

#	include <Axe/Servant.hpp>

#	include <Axe/Communicator.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Adapter::Adapter( const CommunicatorPtr & _communicator, const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name, std::size_t _hostId )
		: Host(_communicator->getService(), _communicator->getConnectionCache(), _endpoint, _name, _hostId)
		, m_communicator(_communicator)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	ProxyPtr Adapter::addUnique( std::size_t _servantId, const std::string & _name, const ServantPtr & _unique )
	{
		ProxyPtr basePrx = this->addServant( _servantId, _unique );

		m_communicator->addUnique( _name, basePrx );

		return basePrx;
	}
	//////////////////////////////////////////////////////////////////////////
	SessionPtr Adapter::makeSession()
	{
		AdapterSessionPtr session = new AdapterSession( m_acceptor.get_io_service(), this, m_connectionCache );

		return session;
	}
}