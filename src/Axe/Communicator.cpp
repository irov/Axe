#	include "pch.hpp"

#	include "Communicator.hpp"

#	include "Adapter.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Communicator::Communicator( boost::asio::io_service & _service )
		: m_service(_service)
	{
		m = ConnectionCache( this );
	}
	//////////////////////////////////////////////////////////////////////////
	boost::asio::io_service & Communicator::getService()
	{
		return m_service;
	}
	//////////////////////////////////////////////////////////////////////////
	const ConnectionCachePtr & Communicator::getConnectionCache() const
	{
		return m_connectionCache;
	}
	//////////////////////////////////////////////////////////////////////////
	void Communicator::initialize( const Proxy_GridManagerPtr & _gridManager )
	{
		m_gridManager = _gridManager;
		m_endpointCache = new EndpointCache( m_gridManager );
	}
	//////////////////////////////////////////////////////////////////////////
	class CommunicatorGridAddAdapterResponse
		: public Response_GridManager_addAdapter
	{
	public:
		CommunicatorGridAddAdapterResponse( 
			const CommunicatorPtr & _communicator
			, const boost::asio::ip::tcp::endpoint & _endpoint
			, const std::string & _name
			, const AdapterCreateResponsePtr & _response )
		: m_communicator(_communicator)
		, m_endpoint(_endpoint)
		, m_name(_name)
		, m_response(_response)
		{
		}

	public:
		void response( std::size_t _id ) override
		{
			AdapterPtr adapter = 
				m_communicator->createAdapterWithId( m_endpoint, m_name, _id );

			m_response->onCreate( adapter );
		}

		void throw_exception( const Axe::Exception & _ex ) override
		{

		}

	protected:
		CommunicatorPtr m_communicator;
		boost::asio::ip::tcp::endpoint m_endpoint;
		std::string m_name;
		AdapterCreateResponsePtr m_response;
	};
	//////////////////////////////////////////////////////////////////////////
	typedef AxeHandle<CommunicatorGridAddAdapterResponse> CommunicatorGridAddAdapterResponsePtr;
	//////////////////////////////////////////////////////////////////////////
	void Communicator::createAdapter( 
		const boost::asio::ip::tcp::endpoint & _endpoint
		, const std::string & _name
		, const AdapterCreateResponsePtr & _response )
	{
		CommunicatorGridAddAdapterResponsePtr gridResponse = 
			new CommunicatorGridAddAdapterResponse( this
			, _endpoint
			, _name
			, _response
			);

		boost::asio::ip::address ip_addr = _endpoint.address();

		std::string addr = ip_addr.to_string(); 
		unsigned short port = _endpoint.port();

		std::stringstream ss;
		ss << addr;
		ss << " ";
		ss << port;

		std::string endpoint = ss.str();

		m_gridManager->addAdapter( _name, endpoint, gridResponse );
	}
	//////////////////////////////////////////////////////////////////////////
	Axe::AdapterPtr Communicator::createAdapterWithId(
		const boost::asio::ip::tcp::endpoint & _endpoint
		, const std::string & _name
		, std::size_t _id )
	{
		AdapterPtr adapter = new Adapter( this, _endpoint, _name, _id );

		return adapter;
	}
	//////////////////////////////////////////////////////////////////////////
	ConnectionPtr Communicator::createConnection( std::size_t _adapterId )
	{
		AdapterConnectionPtr connection = new AdapterConnection( m_service, _adapterId, m_endpointCache, m_connectionCache );

		return connection;
	}
}