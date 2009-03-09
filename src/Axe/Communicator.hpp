#	pragma once

#	include "EndpointCache.hpp"

#	include "AxeProtocols/Player.hpp"

namespace Axe
{
	typedef AxeHandle<class Adapter> AdapterPtr;

	class AdapterCreateResponse
		: virtual public Shared
	{
	public:
		virtual void onCreate( const AdapterPtr & _adapter ) = 0;
		virtual void onFailed() = 0;
	};

	typedef AxeHandle<AdapterCreateResponse> AdapterCreateResponsePtr;

	class Communicator
		: virtual public Shared
		, public ConnectionProvider
	{
	public:
		Communicator( boost::asio::io_service & _service );

	public:
		boost::asio::io_service & getService();

		const ConnectionCachePtr & getConnectionCache() const;

	public:
		void initialize( const Proxy_GridManagerPtr & _gridManager );

	public:
		void createAdapter( 
			const boost::asio::ip::tcp::endpoint & _endpoint
			, const std::string & _name
			, const AdapterCreateResponsePtr & _response 
			);

		Axe::AdapterPtr createAdapterWithId(
			const boost::asio::ip::tcp::endpoint & _endpoint
			, const std::string & _name
			, std::size_t _id );

	protected:
		ConnectionPtr createConnection( std::size_t _adapterId ) override;

	protected:
		boost::asio::io_service & m_service;

		Proxy_GridManagerPtr m_gridManager;

		ConnectionCachePtr m_connectionCache;
		EndpointCachePtr m_endpointCache;
	};

	typedef AxeHandle<Communicator> CommunicatorPtr;
}