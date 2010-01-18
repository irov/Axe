#	include "pch.hpp"

#	include <Axe/Communicator.hpp>

#	include <Axe/Adapter.hpp>
#	include <Axe/Router.hpp>
#	include <Axe/Properties.hpp>

#	include <Axe/AdapterConnection.hpp>

#	include <Axe/ServantFactory.hpp>
#	include <Axe/ServantProvider.hpp>

#	include <AxeProtocols/EvictorManager.hpp>
#	include <AxeProtocols/GridManager.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Communicator::Communicator( const PropertiesPtr & _properties )
		: m_properties(_properties)
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
	const ServantFactoryPtr & Communicator::getServantFactory() const
	{
		return m_servantFactory;
	}
	//////////////////////////////////////////////////////////////////////////
	const ServantProviderPtr & Communicator::getServantProvider() const
	{
		return m_servantProvider;
	}
	//////////////////////////////////////////////////////////////////////////
	void Communicator::connectGrid( const boost::asio::ip::tcp::endpoint & _grid, const CommunicatorConnectResponsePtr & _initializeResponse )
	{

	}
	//////////////////////////////////////////////////////////////////////////
	void Communicator::connectEvictor( const boost::asio::ip::tcp::endpoint & _grid, const CommunicatorConnectResponsePtr & _response )
	{
		
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
	void Communicator::setEvictorManager( const Proxy_EvictorManagerPtr & _evictorManager )
	{
		m_evictorManager = _evictorManager;
		m_servantFactory = new ServantFactory( m_gridManager );
		m_servantProvider = new ServantProvider( m_servantFactory, m_evictorManager );
	}
	//////////////////////////////////////////////////////////////////////////
	const Proxy_EvictorManagerPtr & Communicator::getEvictorManager() const
	{
		return m_evictorManager;
	}
	//////////////////////////////////////////////////////////////////////////
	void Communicator::run()
	{
		m_service.run();
	}
	//////////////////////////////////////////////////////////////////////////
	void Communicator::createAdapterWithId_(
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
	void Communicator::addAdapterResponse_( std::size_t _id
		, const boost::asio::ip::tcp::endpoint & _endpoint
		, const std::string & _name
		, const AdapterCreateResponsePtr & _response )
	{
		this->createAdapterWithId_( _endpoint, _name, _id, _response );
	}
	//////////////////////////////////////////////////////////////////////////
	void Communicator::addAdapterException_( const Axe::Exception & _ex )
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
				boost::bind( &Communicator::addAdapterResponse_, handlePtr(this), _1, _endpoint, _name, _response )
				, boost::bind( &Communicator::addAdapterException_, handlePtr(this), _1 )
				)
			, _name
			, endpoint 
			);
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
	ConnectionPtr Communicator::createConnection( std::size_t _adapterId )
	{
		AdapterConnectionPtr connection = new AdapterConnection( m_service, _adapterId, m_endpointCache, m_connectionCache );

		return connection;
	}
}