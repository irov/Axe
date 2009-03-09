#	include "pch.hpp"
#	include "Adapter.hpp"

#	include "AdapterSession.hpp"
#	include "AdapterConnection.hpp"

#	include "Servant.hpp"

#	include "AxeProtocols/Player.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Adapter::Adapter( const CommunicatorPtr & _communicator, const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name, std::size_t _adapterId )
		: Host(_communicator.getService(), _endpoint, _name)
		, m_communicator(_communicator)
		, m_adapterId(_adapterId)

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
		ProxyPtr base = this->addServantUnique( _unique );

		Proxy_UniquePtr proxyUnique = uncheckedCast<Proxy_UniquePtr>( base );

		m_gridManager->addUnique( _name, proxyUnique, new AdapterAddUniqueResponse() );
	}
	//////////////////////////////////////////////////////////////////////////
	void Adapter::addServant( const ServantPtr & _servant )
	{
		std::size_t servantId = _servant->getServantId();

		bool inserted = this->addServantById( _servant );

		if( inserted == false )
		{
			printf("Adapter::addServant host '%d' already exist servant '%d'\n"
				, m_hostId
				, _servantId 
				);
		}
		
		const ConnectionPtr & cn = m_connectionCache->getConnection( m_adapterId );

		ProxyPtr proxy = new Proxy( servantId, cn );

		return proxy;
	}
	//////////////////////////////////////////////////////////////////////////
	SessionPtr Adapter::makeSession()
	{
		AdapterSessionPtr session = new AdapterSession( m_acceptor.get_io_service(), this, m_connectionCache );

		return session;
	}
}