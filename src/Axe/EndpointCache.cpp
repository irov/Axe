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
	class EndpointCacheResponse_GridManager_getAdapterEndpoint
		: public Response_GridManager_getAdapterEndpoint
	{
	public:
		EndpointCacheResponse_GridManager_getAdapterEndpoint( const EndpointCachePtr & _cache, std::size_t _hostId, const EndpointCallbackPtr & _cb )
			: m_cache(_cache) 
			, m_hostId(_hostId)
			, m_cb(_cb)
		{
		}

	public:
		void response( const std::string & _endpoint )
		{
			std::string addr;
			unsigned short port;
			std::stringstream ss( _endpoint );

			ss >> addr;
			ss >> port;

			boost::asio::ip::address ip_addr = 
				boost::asio::ip::address::from_string( addr );

			boost::asio::ip::tcp::endpoint tcp_endpoint( ip_addr, port );

			m_cache->addEndpoint( m_hostId, tcp_endpoint );

			m_cb->onEndpoint( tcp_endpoint );
		}

		void throw_exception( const Axe::Exception & _ex ) override
		{

		}

	protected:
		EndpointCachePtr m_cache;
		std::size_t m_hostId;
		EndpointCallbackPtr m_cb;
	};
	//////////////////////////////////////////////////////////////////////////
	void EndpointCache::getEndpoint( std::size_t _hostId, const EndpointCallbackPtr & _cb )
	{
		TMapEndpoints::iterator it_found = m_endpoints.find( _hostId );

		if( it_found == m_endpoints.end() )
		{
			m_gridManager->getAdapterEndpoint( 
				new EndpointCacheResponse_GridManager_getAdapterEndpoint( this, _hostId, _cb )
				, _hostId
				);
		}
		else
		{
			_cb->onEndpoint( it_found->second );
		}
	}
}	