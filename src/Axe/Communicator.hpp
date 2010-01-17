#	pragma once

#	include <Axe/ConnectionCache.hpp>
#	include <Axe/EndpointCache.hpp>

namespace Axe
{
	typedef AxeHandle<class Adapter> AdapterPtr;
	typedef AxeHandle<class Adapter> AdapterPtr;
	typedef AxeHandle<class Router> RouterPtr;

	typedef AxeHandle<class ServantFactory> ServantFactoryPtr;
	typedef AxeHandle<class ServantProvider> ServantProviderPtr; 
	
	typedef AxeHandle<class Communicator> CommunicatorPtr;
	

	typedef AxeHandle<class Servant_GridManager> Servant_GridManagerPtr;
	typedef AxeHandle<class Proxy_GridManager> Proxy_GridManagerPtr;
	typedef AxeHandle<class Proxy_EvictorManager> Proxy_EvictorManagerPtr;

	class Exception;

	class CommunicatorConnectResponse
		: virtual public AxeUtil::Shared
	{
	public:
		virtual void onConnect( const CommunicatorPtr & _communicator ) = 0;
		virtual void onFailed() = 0;
	};

	typedef AxeHandle<CommunicatorConnectResponse> CommunicatorConnectResponsePtr;

	class AdapterCreateResponse
		: virtual public AxeUtil::Shared
	{
	public:
		virtual void onCreate( const AdapterPtr & _adapter ) = 0;
		virtual void onFailed() = 0;
	};

	typedef AxeHandle<AdapterCreateResponse> AdapterCreateResponsePtr;

	class RouterCreateResponse
		: virtual public AxeUtil::Shared
	{
	public:
		virtual void onCreate( const RouterPtr & _router ) = 0;
		virtual void onFailed() = 0;
	};

	typedef AxeHandle<RouterCreateResponse> RouterCreateResponsePtr;

	class Communicator
		: virtual public AxeUtil::Shared
		, public ConnectionProvider
	{
	public:
		Communicator();

	public:
		boost::asio::io_service & getService();
		const ConnectionCachePtr & getConnectionCache() const;
		const EndpointCachePtr & getEndpointCache() const;
		const ServantProviderPtr & getServantProvider() const;

	public:
		void connectGrid( const boost::asio::ip::tcp::endpoint & _grid, const CommunicatorConnectResponsePtr & _response );
		void connectEvictor( const boost::asio::ip::tcp::endpoint & _grid, const CommunicatorConnectResponsePtr & _response );

	public:
		void run();

	public:
		void setGridManager( const Proxy_GridManagerPtr & _gridManager );
		const Proxy_GridManagerPtr & getGridManager() const;

		void setEvictorManager( const Proxy_EvictorManagerPtr & _evictorManager );
		const Proxy_EvictorManagerPtr & getEvictorManager() const;

	public:
		void createAdapter( 
			const boost::asio::ip::tcp::endpoint & _endpoint
			, const std::string & _name
			, const AdapterCreateResponsePtr & _response 
			);

	public:
		void createRouter(
			const boost::asio::ip::tcp::endpoint & _endpoint
			, const std::string & _name
			, const RouterCreateResponsePtr & _response 
			);

	protected:
		ConnectionPtr createConnection( std::size_t _adapterId ) override;

	protected:
		void addAdapterResponse_( std::size_t _id
			, const boost::asio::ip::tcp::endpoint & _endpoint
			, const std::string & _name
			, const AdapterCreateResponsePtr & _response 
			);

		void addAdapterException_( const Axe::Exception & _ex );

		void createAdapterWithId_(
			const boost::asio::ip::tcp::endpoint & _endpoint
			, const std::string & _name
			, std::size_t _id 
			, const AdapterCreateResponsePtr & _response );

	protected:
		boost::asio::io_service m_service;

		Proxy_EvictorManagerPtr m_evictorManager;
		Proxy_GridManagerPtr m_gridManager;

		ConnectionCachePtr m_connectionCache;
		EndpointCachePtr m_endpointCache;

		ServantFactoryPtr m_servantFactory;
		ServantProviderPtr m_servantProvider;

		typedef std::map<std::string, AdapterPtr> TMapAdapters;
		TMapAdapters m_adapters; 

		typedef std::map<std::string, RouterPtr> TMapRouters;
		TMapRouters m_routers;
	};

	typedef AxeHandle<Communicator> CommunicatorPtr;
}