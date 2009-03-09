#	include "pch.hpp"

#	include "CommunicatorInitializer.hpp"

#	include "GridConnection.hpp"
#	include "GridConnectResponse.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	class CommunicatorInitializerGridConnectResponse
		: public GridConnectResponse
	{
	public:
		CommunicatorInitializerGridConnectResponse( 
			const CommunicatorInitializerPtr & _communicatorInitializer
			, const CommunicatorInitializerResponsePtr & _communicatorInitializerResponse )
		: m_communicatorInitializer(_communicatorInitializer) 
		, m_communicatorInitializerResponse(_communicatorInitializerResponse)
		{
		}

	public:
		void connectSuccessful( const Proxy_GridManagerPtr & _gridManager ) override
		{
			CommunicatorPtr communicator = m_communicatorInitializer->initializeCommunicator( _gridManager );

			m_communicatorInitializerResponse->onInitialize( communicator );
		}

		void connectFailed() override
		{
			m_communicatorInitializerResponse->onFailed();
		}

	protected:
		CommunicatorInitializerPtr m_communicatorInitializer;
		CommunicatorInitializerResponsePtr m_communicatorInitializerResponse;
	};
	//////////////////////////////////////////////////////////////////////////
	typedef AxeHandle<CommunicatorInitializerGridConnectResponse> CommunicatorInitializerGridConnectResponsePtr;
	//////////////////////////////////////////////////////////////////////////
	void CommunicatorInitializer::run( const boost::asio::ip::tcp::endpoint & _grid, const CommunicatorInitializerResponsePtr & _response )
	{
		CommunicatorInitializerGridConnectResponsePtr gridResponse 
			= new CommunicatorInitializerGridConnectResponse( this, _response );

		m_communicator = new Communicator( m_service );

		const ConnectionCachePtr & connectionCache 
			= m_communicator->getConnectionCache();

		GridConnectionPtr gridConnection
			= new GridConnection( m_service, 0, connectionCache, gridResponse );

		gridConnection->connect( _grid );

		m_service.run();
	}
	//////////////////////////////////////////////////////////////////////////
	CommunicatorPtr CommunicatorInitializer::initializeCommunicator( const Proxy_GridManagerPtr & _gridManager )
	{
		m_communicator->initialize( _gridManager );

		return m_communicator;
	}
}