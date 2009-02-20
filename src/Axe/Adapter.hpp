#	pragma once

#	include "Host.hpp"

#	include "GridConnection.hpp"
#	include "GridConnectResponse.hpp"

#	include "AxeProtocols/Player.hpp"

namespace Axe
{
	typedef AxeHandle<class AdapterSession> AdapterSessionPtr;
	typedef AxeHandle<class Connection> ConnectionPtr;

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
		Adapter( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name );

	public:
		void initialize( const boost::asio::ip::tcp::endpoint & _grid, const AdapterInitializeResponsePtr & _response );

	public:
		void start( const Proxy_GridManagerPtr & _gridManager, std::size_t _endpointId );

	public:
		void addUnique( const std::string & _name, const Servant_UniquePtr & _unique );

	protected:
		SessionPtr makeSession() override;

	protected:
		ConnectionPtr createConnection( std::size_t _endpointId ) override;

	protected:
		Proxy_GridManagerPtr m_gridManager;
	};

	typedef AxeHandle<Adapter> AdapterPtr;
}