#	include "pch.hpp"
#	include <Axe/Adapter.hpp>

#	include <Axe/Communicator.hpp>

#	include <Axe/AdapterSession.hpp>
#	include <Axe/AdapterConnection.hpp>

#	include <Axe/Servant.hpp>

#	include <AxeProtocols/Player.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Adapter::Adapter( const CommunicatorPtr & _communicator, const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name, std::size_t _hostId )
		: Host(_communicator->getService(), _communicator->getConnectionCache(), _endpoint, _name, _hostId)
		, m_endpointCache(_communicator->getEndpointCache())
		, m_gridManager(_communicator->getGridManager())
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Adapter::start()
	{
		Service::accept();
	}
	//////////////////////////////////////////////////////////////////////////
	class AdapterAddUniqueResponse
		: public Response_GridManager_addUnique
	{
	protected:
		void response() override
		{
		}

	protected:
		void throw_exception( const Axe::Exception & _ex ) override
		{
		}
	};
	//////////////////////////////////////////////////////////////////////////
	void Adapter::addUnique( const std::string & _name, const Servant_UniquePtr & _unique )
	{
		ProxyPtr base = this->addServant( _unique );

		Proxy_UniquePtr proxyUnique = uncheckedCast<Proxy_UniquePtr>( base );

		m_gridManager->addUnique( _name, proxyUnique, new AdapterAddUniqueResponse() );
	}
	//////////////////////////////////////////////////////////////////////////
	SessionPtr Adapter::makeSession()
	{
		AdapterSessionPtr session = new AdapterSession( m_acceptor.get_io_service(), this, m_connectionCache );

		return session;
	}
}