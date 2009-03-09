#	pragma once

#	include "Communicator.hpp"

#	include "AxeProtocols/Player.hpp"

namespace Axe
{
	class CommunicatorInitializerResponse
		: virtual public Shared
	{
	public:
		virtual void onInitialize( const CommunicatorPtr & _communicator ) = 0;
		virtual void onFailed() = 0;
	};

	typedef AxeHandle<CommunicatorInitializerResponse> CommunicatorInitializerResponsePtr;

	class CommunicatorInitializer
		: virtual public Shared
	{
	public:
		void run( const boost::asio::ip::tcp::endpoint & _grid, const CommunicatorInitializerResponsePtr & _response );

	public:
		CommunicatorPtr initializeCommunicator( const Proxy_GridManagerPtr & _gridManager );

	protected:
		CommunicatorPtr m_communicator;
		boost::asio::io_service m_service;
	};

	typedef AxeHandle<CommunicatorInitializer> CommunicatorInitializerPtr;
}