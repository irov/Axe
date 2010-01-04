#	include "pch.hpp"

#	include <Axe/EndpointCache.hpp>

#	include <AxeProtocols/Player.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	EndpointCache::EndpointCache( const ProxyPtr & _gridManagerPrx )
		: m_gridManagerPrx(_gridManagerPrx)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void EndpointCache::addEndpoint( std::size_t _hostId, const boost::asio::ip::tcp::endpoint & _endpoint )
	{
		m_endpoints.insert( std::make_pair(_hostId, _endpoint) );
	}
	//////////////////////////////////////////////////////////////////////////
	void EndpointCache::getEndpoint( std::size_t _hostId, const EndpointCallbackPtr & _cb )
	{
		TMapEndpoints::iterator it_found = m_endpoints.find( _hostId );

		if( it_found == m_endpoints.end() )
		{
			this->provideEndpoint( _hostId, _cb );
		}
		else
		{
			_cb->onEndpoint( it_found->second );
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void EndpointCache::provideEndpoint( std::size_t _hostId, const EndpointCallbackPtr & _cb )
	{
		TMapWantedEndpoints::iterator it_found = m_wantedEndpoints.find( _hostId );

		if( it_found == m_wantedEndpoints.end() )
		{
			uncheckedCast<Proxy_GridManagerPtr>(m_gridManagerPrx)->getAdapterEndpoint_async( 
				bindResponse( boost::bind( &EndpointCache::getEndpointResponse, handlePtr(this), _1, _hostId, _cb )
				, noneExceptionFilter() )
				, _hostId
				);

			TListEndpointResponses responses;
			responses.push_back( _cb );

			it_found = m_wantedEndpoints.insert( std::make_pair(_hostId, responses) ).first;
		}

		it_found->second.push_back( _cb );
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

		TMapWantedEndpoints::iterator it_found = m_wantedEndpoints.find( _hostId );

		for( TListEndpointResponses::iterator
			it = it_found->second.begin(),
			it_end = it_found->second.end();
		it != it_end;
		++it )
		{
			(*it)->onEndpoint( tcp_endpoint );
		}

		m_wantedEndpoints.erase( it_found );
	}
}	