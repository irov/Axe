#	include "pch.hpp"

#	include <Axe/Communicator.hpp>

#	include <Axe/GridConnection.hpp>

#	include <Axe/Adapter.hpp>
#	include <Axe/Router.hpp>
#	include <Axe/Grid.hpp>

#	include <AxeProtocols/GridManager.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Communicator::Communicator()
	{	
		m_connectionCache = new ConnectionCache( this );
	}
	//////////////////////////////////////////////////////////////////////////
	boost::asio::io_service & Communicator::getService()
	{
		return m_service;
	}
	//////////////////////////////////////////////////////////////////////////
	const ConnectionCachePtr & Communicator::getConnectionCache() const
	{
		return m_connectionCache;
	}
	//////////////////////////////////////////////////////////////////////////
	const EndpointCachePtr & Communicator::getEndpointCache() const
	{
		return m_endpointCache;
	}
	//////////////////////////////////////////////////////////////////////////
	class CommunicatorGridConnectResponse
		: public GridConnectResponse
	{
	public:
		CommunicatorGridConnectResponse( 
			const CommunicatorPtr & _communicator
			, const CommunicatorConnectResponsePtr & _initializeResponse )
			: m_communicator(_communicator) 
			, m_connectResponse(_initializeResponse)
		{
		}

	public:
		void connectSuccessful( const Proxy_GridManagerPtr & _gridManager ) override
		{
			m_communicator->setGridManager( _gridManager );
			
			m_connectResponse->onConnect( m_communicator );
		}

		void connectFailed() override
		{
			m_connectResponse->onFailed();
		}

	protected:
		CommunicatorPtr m_communicator;
		CommunicatorConnectResponsePtr m_connectResponse;
	};
	//////////////////////////////////////////////////////////////////////////
	typedef AxeHandle<CommunicatorGridConnectResponse> CommunicatorGridConnectResponsePtr;
	//////////////////////////////////////////////////////////////////////////
	void Communicator::connectGrid( const boost::asio::ip::tcp::endpoint & _grid, const CommunicatorConnectResponsePtr & _initializeResponse )
	{
		CommunicatorGridConnectResponsePtr gridResponse 
			= new CommunicatorGridConnectResponse( this, _initializeResponse );

		GridConnectionPtr gridConnection
			= new GridConnection( m_service, 0, m_connectionCache, gridResponse );

		gridConnection->connect( _grid );
	}
	//////////////////////////////////////////////////////////////////////////
	void Communicator::setGridManager( const Proxy_GridManagerPtr & _gridManager )
	{
		m_gridManager = _gridManager;
		m_endpointCache = new EndpointCache( m_gridManager );
	}
	//////////////////////////////////////////////////////////////////////////
	const Proxy_GridManagerPtr & Communicator::getGridManager() const
	{
		return m_gridManager;
	}
	//////////////////////////////////////////////////////////////////////////
	void Communicator::run()
	{
		m_service.run();
	}
	//////////////////////////////////////////////////////////////////////////
	void Communicator::addAdapterResponse( std::size_t _id
		, const boost::asio::ip::tcp::endpoint & _endpoint
		, const std::string & _name
		, const AdapterCreateResponsePtr & _response )
	{
		this->createAdapterWithId( _endpoint, _name, _id, _response );
	}
	//////////////////////////////////////////////////////////////////////////
	void Communicator::addAdapterException( const Axe::Exception & _ex )
	{
		
	}
	//////////////////////////////////////////////////////////////////////////
	void Communicator::createAdapter( 
		const boost::asio::ip::tcp::endpoint & _endpoint
		, const std::string & _name
		, const AdapterCreateResponsePtr & _response )
	{
		boost::asio::ip::address ip_addr = _endpoint.address();

		std::string addr = ip_addr.to_string(); 
		unsigned short port = _endpoint.port();

		std::stringstream ss;
		ss << addr;
		ss << " ";
		ss << port;

		std::string endpoint = ss.str();

		m_gridManager->addAdapter_async( 
			bindResponse( 
				boost::bind( &Communicator::addAdapterResponse, handlePtr(this), _1, _endpoint, _name, _response )
				, boost::bind( &Communicator::addAdapterException, handlePtr(this), _1 )
				)
			, _name
			, endpoint 
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Communicator::createAdapterWithId(
		const boost::asio::ip::tcp::endpoint & _endpoint
		, const std::string & _name
		, std::size_t _id 
		, const AdapterCreateResponsePtr & _response )
	{
		AdapterPtr adapter = new Adapter( this, _endpoint, _name, _id );

		m_hosts.insert( std::make_pair( _name, adapter ) );

		if( _response )
		{
			_response->onCreate( adapter );
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void Communicator::createRouter(
		const boost::asio::ip::tcp::endpoint & _endpoint
		, const std::string & _name
		, const RouterCreateResponsePtr & _response )
	{
		RouterPtr router = new Router( this, _endpoint, _name );

		m_routers.insert( std::make_pair( _name, router ) );

		if( _response )
		{
			_response->onCreate( router );
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void Communicator::createGrid( 
		const boost::asio::ip::tcp::endpoint & _endpoint
		, const std::string & _name
		, const Servant_GridManagerPtr & _servant 
		, const GridCreateResponsePtr & _response )
	{
		GridPtr grid = new Grid( m_service, _endpoint, _name );

		const Proxy_GridManagerPtr & gridManager = grid->addGridManager( _servant );

		this->setGridManager( gridManager );

		grid->accept();

		m_hosts.insert( std::make_pair("Grid", grid) );

		_response->onCreate( grid );
	}
	//////////////////////////////////////////////////////////////////////////
	const ConnectionPtr & Communicator::getConnection( std::size_t _hostId )
	{
		const ConnectionPtr & connection = m_connectionCache->getConnection( _hostId );

		return connection;
	}
	//////////////////////////////////////////////////////////////////////////
	ConnectionPtr Communicator::createConnection( std::size_t _adapterId )
	{
		AdapterConnectionPtr connection = new AdapterConnection( m_service, _adapterId, m_endpointCache, m_connectionCache );

		return connection;
	}
}