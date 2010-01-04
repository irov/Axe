#	pragma once

#	include <Axe/ConnectionCache.hpp>
#	include <Axe/EndpointCache.hpp>
#	include <Axe/Grid.hpp>

namespace Axe
{
	typedef AxeHandle<class Adapter> AdapterPtr;
	typedef AxeHandle<class Router> RouterPtr;
	typedef AxeHandle<class Communicator> CommunicatorPtr;

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

	class GridCreateResponse
		: virtual public AxeUtil::Shared
	{
	public:
		virtual void onCreate( const GridPtr & _grid ) = 0;
		virtual void onFailed() = 0;
	};

	typedef AxeHandle<GridCreateResponse> GridCreateResponsePtr;

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

	public:
		void connect( const boost::asio::ip::tcp::endpoint & _grid, const CommunicatorConnectResponsePtr & _initializeResponse );

	public:
		void run();

	public:
		void setGridManager( const ProxyPtr & _gridManager );

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

	public:
		void createGrid( 
			const boost::asio::ip::tcp::endpoint & _endpoint
			, const std::string & _name
			, const ServantPtr & _servant 
			, const GridCreateResponsePtr & _response );

	public:
		void addUnique( const std::string & _name, const ProxyPtr & _proxy );
		void getUnique( const std::string & _name, const boost::function<> & _response );

	public:
		const ConnectionPtr & getConnection( std::size_t _hostId );

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

		ProxyPtr m_gridManagerPrx;

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