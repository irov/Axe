#	include "pch.hpp"
#	include "Adapter.hpp"

#	include "AdapterSession.hpp"
#	include "AdapterConnection.hpp"

#	include "Servant.hpp"

#	include "AxeProtocols/Player.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	class AdapterGridConnectResponse
		: public GridConnectResponse
		, public Response_GridManager_addAdapter
	{
	public:
		AdapterGridConnectResponse( const AdapterPtr & _adapter, const AdapterInitializeResponsePtr & _response )
			: m_adapter(_adapter)
			, m_response( _response )
		{
		}

	public:
		void connectSuccessful( const Proxy_GridManagerPtr & _gridManager ) override
		{
			m_gridManager = _gridManager;

			const std::string & name = m_adapter->getName();

			m_gridManager->addAdapter( name, this );
		}

		void connectFailed() override
		{
			m_response->onFailed();
		}

	public:
		void response( std::size_t _id ) override
		{
			m_adapter->start( m_gridManager, _id );
			m_response->onInitialize( m_adapter );
		}

	protected:
		AdapterPtr m_adapter;
		AdapterInitializeResponsePtr m_response;

		Proxy_GridManagerPtr m_gridManager;
	};

	typedef AxeHandle<AdapterGridConnectResponse> AdapterGridConnectResponsePtr;

	//////////////////////////////////////////////////////////////////////////
	Adapter::Adapter( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name )
		: Host(_endpoint, _name)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Adapter::initialize( const boost::asio::ip::tcp::endpoint & _grid, const AdapterInitializeResponsePtr & _response )
	{
		AdapterGridConnectResponsePtr gridResponse = new AdapterGridConnectResponse( this, _response );

		GridConnectionPtr gridConnection
			= new GridConnection( m_service, m_connectionCache, gridResponse );

		gridConnection->connect( _grid );
	}
	//////////////////////////////////////////////////////////////////////////
	void Adapter::start( const Proxy_GridManagerPtr & _gridManager, std::size_t _endpointId )
	{
		m_gridManager = _gridManager;

		this->refreshServantEndpoint( _endpointId );
		
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
		AdapterSessionPtr session = new AdapterSession( m_acceptor.get_io_service(), this );

		return session;
	}
	//////////////////////////////////////////////////////////////////////////
	ConnectionPtr Adapter::createConnection( std::size_t _endpointId )
	{
		AdapterConnectionPtr connection = new AdapterConnection( m_acceptor.get_io_service(), m_connectionCache, _endpointId );

		return connection;
	}
}