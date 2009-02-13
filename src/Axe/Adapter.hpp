#	pragma once

#	include "Host.hpp"

#	include "GridConnection.hpp"
#	include "GridConnectResponse.hpp"

namespace Axe
{
	typedef AxeHandle<class AdapterSession> AdapterSessionPtr;
	typedef AxeHandle<class Connection> ConnectionPtr;

	class Adapter
		: public Host
		, public GridConnectResponse
	{
	public:
		Adapter( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name );

	public:
		void initialize( const boost::asio::ip::tcp::endpoint & _grid );

	public:
		void start( std::size_t _endpointId );

	protected:
		SessionPtr makeSession() override;

	protected:
		ConnectionPtr createConnection( std::size_t _endpointId ) override;

	protected:
		void connectSuccessful( const Proxy_GridManagerPtr & _gridManager ) override;
		void connectFailed() override;

	protected:
		GridConnectionPtr m_gridConnection;
	};

	typedef AxeHandle<Adapter> AdapterPtr;
}