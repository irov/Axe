#	pragma once

#	include <AxeUtil/Shared.hpp>

#	include <Axe/Proxy.hpp>

namespace Axe
{
	class EndpointCacheResponse
		: virtual public AxeUtil::Shared
	{
	public:
		virtual void onEndpoint( const boost::asio::ip::tcp::endpoint & _endpoint ) = 0;
	};

	typedef AxeHandle<EndpointCacheResponse> EndpointCallbackPtr;

	class EndpointCache
		: virtual public AxeUtil::Shared
	{
	public:
		EndpointCache( const ProxyPtr & _gridManager );

	public:
		void addEndpoint( std::size_t _hostId, const boost::asio::ip::tcp::endpoint & _endpoint );
		void getEndpoint( std::size_t _hostId, const EndpointCallbackPtr & _cb );

	protected:
		void getEndpointResponse( const std::string & _endpoint, std::size_t _hostId, const EndpointCallbackPtr & _cb );

	protected:
		void provideEndpoint( std::size_t _hostId, const EndpointCallbackPtr & _cb );

	protected:
		ProxyPtr m_gridManagerPrx;

		typedef std::map<std::size_t, boost::asio::ip::tcp::endpoint> TMapEndpoints;
		TMapEndpoints m_endpoints;

		typedef std::list<EndpointCallbackPtr> TListEndpointResponses;
		typedef std::map<std::size_t, TListEndpointResponses> TMapWantedEndpoints;
		TMapWantedEndpoints m_wantedEndpoints;
	};

	typedef AxeHandle<EndpointCache> EndpointCachePtr;
}