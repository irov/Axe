#	pragma once

#	include <Axe/ConnectionCache.hpp>
#	include <Axe/EndpointCache.hpp>
#	include <Axe/Grid.hpp>

#	include <AxeProtocols/Player.hpp>

namespace Axe
{
	typedef AxeHandle<class Adapter> AdapterPtr;
	typedef AxeHandle<class Router> RouterPtr;
	typedef AxeHandle<class Communicator> CommunicatorPtr;

	class CommunicatorInitializeResponse
		: virtual public Shared
	{
	public:
		virtual void onInitialize( const CommunicatorPtr & _communicator ) = 0;
		virtual void onFailed() = 0;
	};

	typedef AxeHandle<CommunicatorInitializeResponse> CommunicatorInitializeResponsePtr;

	class AdapterCreateResponse
		: virtual public Shared
	{
	public:
		virtual void onCreate( const AdapterPtr & _adapter ) = 0;
		virtual void onFailed() = 0;
	};

	typedef AxeHandle<AdapterCreateResponse> AdapterCreateResponsePtr;

	class RouterCreateResponse
		: virtual public Shared
	{
	public:
		virtual void onCreate( const RouterPtr & _router ) = 0;
		virtual void onFailed() = 0;
	};

	typedef AxeHandle<RouterCreateResponse> RouterCreateResponsePtr;

	class Communicator
		: virtual public Shared
		, public ConnectionProvider
	{
	public:
		Communicator();

	public:
		boost::asio::io_service & getService();
		const ConnectionCachePtr & getConnectionCache() const;
		const EndpointCachePtr & getEndpointCache() const;
		const Proxy_GridManagerPtr & getGridManager() const;

	public:
		void initialize( const boost::asio::ip::tcp::endpoint & _grid, const CommunicatorInitializeResponsePtr & _initializeResponse );
		void initialize( const Proxy_GridManagerPtr & _gridManager, const CommunicatorInitializeResponsePtr & _initializeResponse );

		void initializeGrid( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name, const CommunicatorInitializeResponsePtr & _initializeResponse );

	public:
		void run();

	public:
		void onInitialize( const Proxy_GridManagerPtr & _gridManager, const CommunicatorInitializeResponsePtr & _initializeResponse );

	public:
		void createAdapter( 
			const boost::asio::ip::tcp::endpoint & _endpoint
			, const std::string & _name
			, const AdapterCreateResponsePtr & _response 
			);

		void createAdapterWithId(
			const boost::asio::ip::tcp::endpoint & _endpoint
			, const std::string & _name
			, std::size_t _id 
			, const AdapterCreateResponsePtr & _response );

	public:
		void createRouter(
			const boost::asio::ip::tcp::endpoint & _endpoint
			, const std::string & _name
			, const RouterCreateResponsePtr & _response 
			);

	protected:
		ConnectionPtr createConnection( std::size_t _adapterId, const ConnectionCachePtr & _connectionCache ) override;

	protected:
		void addAdapterResponse( std::size_t _id
			, const boost::asio::ip::tcp::endpoint & _endpoint
			, const std::string & _name
			, const AdapterCreateResponsePtr & _response 
			);

		void addAdapterException( const Axe::Exception & _ex );

	protected:
		boost::asio::io_service m_service;

		Proxy_GridManagerPtr m_gridManager;

		ConnectionCachePtr m_connectionCache;
		EndpointCachePtr m_endpointCache;

		GridPtr m_grid;

		typedef std::map<std::string, AdapterPtr> TMapAdapters;
		TMapAdapters m_adapters;

		typedef std::map<std::string, RouterPtr> TMapRouters;
		TMapRouters m_routers;
	};

	typedef AxeHandle<Communicator> CommunicatorPtr;
}