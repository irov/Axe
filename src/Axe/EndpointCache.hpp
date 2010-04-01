#	pragma once

#	include <AxeUtil/Shared.hpp>

namespace Axe
{
	typedef AxeHandle<class Proxy_GridManager> Proxy_GridManagerPtr;

	typedef boost::function1<void, boost::asio::ip::tcp::endpoint> FEndpointCallback;

	class EndpointCache
		: virtual public AxeUtil::Shared
	{
	public:
		EndpointCache( const Proxy_GridManagerPtr & _gridManager );

	public:
		void addEndpoint( std::size_t _adapterId, const boost::asio::ip::tcp::endpoint & _endpoint );
		void getEndpoint( std::size_t _adapterId, const FEndpointCallback & _cb );

	protected:
		void getEndpointResponse( const std::string & _endpoint, std::size_t _adapterId, const FEndpointCallback & _cb );

	protected:
		void provideEndpoint( std::size_t _adapterId, const FEndpointCallback & _cb );

	protected:
		Proxy_GridManagerPtr m_gridManager;

		typedef std::map<std::size_t, boost::asio::ip::tcp::endpoint> TMapEndpoints;
		TMapEndpoints m_endpoints;

		typedef std::list<FEndpointCallback> TListEndpointResponses;
		typedef std::map<std::size_t, TListEndpointResponses> TMapWantedEndpoints;
		TMapWantedEndpoints m_wantedEndpoints;
	};

	typedef AxeHandle<EndpointCache> EndpointCachePtr;
}