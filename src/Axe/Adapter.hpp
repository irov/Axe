#	pragma once

#	include <Axe/Host.hpp>

#	include <Axe/EndpointCache.hpp>

#	include <AxeProtocols/Player.hpp>

namespace Axe
{
	typedef AxeHandle<class AdapterSession> AdapterSessionPtr;
	typedef AxeHandle<class Connection> ConnectionPtr;
	typedef AxeHandle<class Communicator> CommunicatorPtr;

	typedef AxeHandle<class Adapter> AdapterPtr;

	class AdapterInitializeResponse
		: virtual public Shared
	{
	public:
		virtual void onInitialize( const Axe::AdapterPtr & _adapter ) = 0;
		virtual void onFailed() = 0;
	};

	typedef AxeHandle<AdapterInitializeResponse> AdapterInitializeResponsePtr;

	class Adapter
		: public Host		
	{
	public:
		Adapter( const CommunicatorPtr & _communicator, const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name, std::size_t _hostId );

	public:
		void start();

	public:
		Proxy_UniquePtr addUnique( std::size_t _servantId, const std::string & _name, const Servant_UniquePtr & _unique );

	protected:
		SessionPtr makeSession() override;

	protected:
		Proxy_GridManagerPtr m_gridManager;
		EndpointCachePtr m_endpointCache;
	};

	typedef AxeHandle<Adapter> AdapterPtr;
}