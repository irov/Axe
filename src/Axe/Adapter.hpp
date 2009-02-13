#	pragma once

#	include "Host.hpp"

#	include "GridConnection.hpp"
#	include "AdapterConnectResponse.hpp"

namespace Axe
{
	typedef AxeHandle<class AdapterSession> AdapterSessionPtr;
	typedef AxeHandle<class Connection> ConnectionPtr;

	class Adapter
		: public Host
		, public AdapterConnectResponse
	{
	public:
		Adapter( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name );

	public:
		void initialize( const boost::asio::ip::tcp::endpoint & _grid );

	protected:
		SessionPtr makeSession() override;

	protected:
		ConnectionPtr createConnection( std::size_t _endpointId ) override;

	protected:
		void connectSuccessful( std::size_t _endpointId ) override;
		void connectFailed() override;

	protected:
		GridConnectionPtr m_gridConnection;
	};

	typedef AxeHandle<Adapter> AdapterPtr;
}