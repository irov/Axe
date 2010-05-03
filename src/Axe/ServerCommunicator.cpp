#	include "pch.hpp"

#	include "ServerCommunicator.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	ServerCommunicator::ServerCommunicator( const boost::property_tree::ptree & _properties )
		: Communicator(_properties)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void ServerCommunicator::initialize( const TCommunicatorConnectResponse & _response, const TCommunicatorException & _ex )
	{
		std::string address = m_properties.get<std::string>("Grid/Endpoints/Address");
		std::size_t port = m_properties.get<std::size_t>("Grid/Endpoints/Port");

		boost::asio::ip::tcp::endpoint ep( boost::asio::ip::address::from_string(address), port );

		const ProxyConnectionProviderPtr & proxyConnectionProvider 
			= m_connectionCache->getProxyServantProvider( "Grid", ep );

		m_grid = new Proxy_GridManager( 0, proxyConnectionProvider );

		return true;
	}
	//////////////////////////////////////////////////////////////////////////
	void ServerCommunicator::createAdapterResponse( std::size_t _id
		, const ProxyPtr & _evictor
		, const boost::asio::ip::tcp::endpoint & _endpoint
		, const std::string & _name
		, const TCommunicatorCreateAdapterResponse & _response )
	{
		AdapterPtr adapter = new Adapter( this, _endpoint, _id, _evictor );

		m_adapters.insert( std::make_pair( _name, adapter ) );

		_response(adapter);
	}
	//////////////////////////////////////////////////////////////////////////
	void ServerCommunicator::createAdapter( const std::string & _name
		, const boost::asio::ip::tcp::endpoint & _endpoint
		, const TCommunicatorCreateAdapterResponse & _response
		, const TCommunicatorException & _exception )
	{
		boost::asio::ip::address ip_addr = _endpoint.address();

		std::string addr = ip_addr.to_string(); 
		unsigned short port = _endpoint.port();

		std::stringstream ss;
		ss << addr;
		ss << " ";
		ss << port;

		std::string endpoint = ss.str();

		m_grid->addAdapter_async( 
			bindResponse( 
			boost::bind( &Communicator::addAdapterResponse_, handlePtr(this), _1, _endpoint, _name, _response )
			, _exception
			)
			, _name
			, endpoint 
			);
	}
}