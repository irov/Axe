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
			m_communicator->onInitialize( _gridManager, m_initializeResponse );
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
	void Communicator::run( const boost::asio::ip::tcp::endpoint & _grid, const CommunicatorInitializeResponsePtr & _initializeResponse )
	{
		m_connectionCache = new ConnectionCache( this );

		CommunicatorGridConnectResponsePtr gridResponse 
			= new CommunicatorGridConnectResponse( this, _initializeResponse );

		GridConnectionPtr gridConnection
			= new GridConnection( m_service, 0, m_connectionCache, gridResponse );

		gridConnection->connect( _grid );

		m_service.run();
	}
	//////////////////////////////////////////////////////////////////////////
	void Communicator::onInitialize( const Proxy_GridManagerPtr & _gridManager, const CommunicatorInitializeResponsePtr & _initializeResponse )
	{
		m_gridManager = _gridManager;
		m_endpointCache = new EndpointCache( m_gridManager );

		_initializeResponse->onInitialize( this );
	}
	//////////////////////////////////////////////////////////////////////////
	class CommunicatorGridAddAdapterResponse
		: public Response_GridManager_addAdapter
	{
	public:
		CommunicatorGridAddAdapterResponse( 
			const CommunicatorPtr & _communicator
			, const boost::asio::ip::tcp::endpoint & _endpoint
			, const std::string & _name
			, const AdapterCreateResponsePtr & _response )
		: m_communicator(_communicator)
		, m_endpoint(_endpoint)
		, m_name(_name)
		, m_response(_response)
		{
		}

	public:
		void response( std::size_t _id ) override
		{
			m_communicator->createAdapterWithId( m_endpoint, m_name, _id, m_response );
		}

		void throw_exception( const Axe::Exception & _ex ) override
		{

		}

	protected:
		CommunicatorPtr m_communicator;
		boost::asio::ip::tcp::endpoint m_endpoint;
		std::string m_name;
		AdapterCreateResponsePtr m_response;
	};
	//////////////////////////////////////////////////////////////////////////
	typedef AxeHandle<CommunicatorGridAddAdapterResponse> CommunicatorGridAddAdapterResponsePtr;
	//////////////////////////////////////////////////////////////////////////
	void Communicator::createAdapter( 
		const boost::asio::ip::tcp::endpoint & _endpoint
		, const std::string & _name
		, const AdapterCreateResponsePtr & _response )
	{
		CommunicatorGridAddAdapterResponsePtr gridResponse = 
			new CommunicatorGridAddAdapterResponse( this
			, _endpoint
			, _name
			, _response
			);

		boost::asio::ip::address ip_addr = _endpoint.address();

		std::string addr = ip_addr.to_string(); 
		unsigned short port = _endpoint.port();

		std::stringstream ss;
		ss << addr;
		ss << " ";
		ss << port;

		std::string endpoint = ss.str();

		m_gridManager->addAdapter( _name, endpoint, gridResponse );
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