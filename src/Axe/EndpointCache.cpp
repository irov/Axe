#	include "pch.hpp"

#	include <Axe/EndpointCache.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	EndpointCache::EndpointCache( const Proxy_GridManagerPtr & _gridManager )
		: m_gridManager(_gridManager)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void EndpointCache::addEndpoint( std::size_t _hostId, const boost::asio::ip::tcp::endpoint & _endpoint )
	{
		m_endpoints.insert( std::make_pair(_hostId, _endpoint) );
	}
	//////////////////////////////////////////////////////////////////////////
	void EndpointCache::getEndpointResponse( const std::string & _endpoint, std::size_t _hostId, const EndpointCallbackPtr & _cb )
	{
		std::string addr;
		unsigned short port;
		std::stringstream ss( _endpoint );

		ss >> addr;
		ss >> port;

		boost::asio::ip::address ip_addr = 
			boost::asio::ip::address::from_string( addr );

		boost::asio::ip::tcp::endpoint tcp_endpoint( ip_addr, port );

		this->addEndpoint( _hostId, tcp_endpoint );

		_cb->onEndpoint( tcp_endpoint );
	}
	//////////////////////////////////////////////////////////////////////////
	void EndpointCache::getEndpoint( std::size_t _hostId, const EndpointCallbackPtr & _cb )
	{
		TMapEndpoints::iterator it_found = m_endpoints.find( _hostId );

		if( it_found == m_endpoints.end() )
		{
			m_gridManager->getAdapterEndpoint_async( 
				bindResponse( boost::bind( &EndpointCache::getEndpointResponse, handlePtr(this), _1, _hostId, _cb )
					, noneExceptionFilter() )
				, _hostId
				);
		}
		else
		{
			_cb->onEndpoint( it_found->second );
		}
	}
}	