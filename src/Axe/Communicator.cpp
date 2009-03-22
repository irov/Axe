#	include "pch.hpp"

#	include <Axe/Communicator.hpp>

#	include <Axe/GridConnection.hpp>

#	include <Axe/Adapter.hpp>
#	include <Axe/Router.hpp>

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
	const Proxy_GridManagerPtr & Communicator::getGridManager() const
	{
		return m_gridManager;
	}
	//////////////////////////////////////////////////////////////////////////
	class CommunicatorGridConnectResponse
		: public GridConnectResponse
	{
	public:
		CommunicatorGridConnectResponse( 
			const CommunicatorPtr & _communicator
			, const CommunicatorInitializeResponsePtr & _initializeResponse )
			: m_communicator(_communicator) 
			, m_initializeResponse(_initializeResponse)
		{
		}

	public:
		void connectSuccessful( const Proxy_GridManagerPtr & _gridManager ) override
		{
			m_communicator->initialize( _gridManager, m_initializeResponse );
		}

		void connectFailed() override
		{
			m_initializeResponse->onFailed();
		}

	protected:
		CommunicatorPtr m_communicator;
		CommunicatorInitializeResponsePtr m_initializeResponse;
	};
	//////////////////////////////////////////////////////////////////////////
	typedef AxeHandle<CommunicatorGridConnectResponse> CommunicatorGridConnectResponsePtr;
	//////////////////////////////////////////////////////////////////////////
	void Communicator::initialize( const boost::asio::ip::tcp::endpoint & _grid, const CommunicatorInitializeResponsePtr & _initializeResponse )
	{
		CommunicatorGridConnectResponsePtr gridResponse 
			= new CommunicatorGridConnectResponse( this, _initializeResponse );

		GridConnectionPtr gridConnection
			= new GridConnection( m_service, 0, m_connectionCache, gridResponse );

		gridConnection->connect( _grid );
	}
	//////////////////////////////////////////////////////////////////////////
	void Communicator::initializeGrid( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name, const CommunicatorInitializeResponsePtr & _initializeResponse )
	{
		m_grid = new Grid( m_service, _endpoint, _name );

		const Proxy_GridManagerPtr & gridManager = m_grid->initialize();

		this->initialize( gridManager, _initializeResponse );
	}
	//////////////////////////////////////////////////////////////////////////
	void Communicator::initialize( const Proxy_GridManagerPtr & _gridManager, const CommunicatorInitializeResponsePtr & _initializeResponse )
	{
		m_gridManager = _gridManager;
		m_endpointCache = new EndpointCache( m_gridManager );

		_initializeResponse->onInitialize( this );
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

		m_adapters.insert( std::make_pair( _name, adapter ) );

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
	ConnectionPtr Communicator::createConnection( std::size_t _adapterId, const ConnectionCachePtr & _connectionCache )
	{
		AdapterConnectionPtr connection = new AdapterConnection( m_service, _adapterId, m_endpointCache, _connectionCache );

		return connection;
	}
}