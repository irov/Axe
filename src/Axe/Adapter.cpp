#	include "pch.hpp"
#	include "Adapter.hpp"

#	include "AdapterSession.hpp"
#	include "AdapterConnection.hpp"

#	include "Servant.hpp"

#	include "AxeProtocols/Player.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Adapter::Adapter( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name )
		: Host(_endpoint, _name)
	{
		m_gridConnection = new GridConnection( m_service, m_connectionCache, this );
	}
	//////////////////////////////////////////////////////////////////////////
	void Adapter::initialize( const boost::asio::ip::tcp::endpoint & _grid )
	{
		m_gridConnection->connect( _grid );
	}
	//////////////////////////////////////////////////////////////////////////
	void Adapter::start( std::size_t _endpointId )
	{
		this->refreshServantEndpoint( _endpointId );
		
		Service::accept();

		this->onStart();
	}
	//////////////////////////////////////////////////////////////////////////
	void Adapter::onStart()
	{
		//Empty
	}
	//////////////////////////////////////////////////////////////////////////
	SessionPtr Adapter::makeSession()
	{
		AdapterSessionPtr session = new AdapterSession( m_acceptor.get_io_service(), this );

		return session;
	}
	//////////////////////////////////////////////////////////////////////////
	ConnectionPtr Adapter::createConnection( std::size_t _endpointId )
	{
		AdapterConnectionPtr connection = new AdapterConnection( m_acceptor.get_io_service(), m_connectionCache, _endpointId );

		return connection;
	}
	//////////////////////////////////////////////////////////////////////////
	class AdapterGridRegistrationResponse
		: public Response_GridManager_addAdapter
	{
	public:
		AdapterGridRegistrationResponse( const AdapterPtr & _adapter )
			: m_adapter(_adapter)
		{
		}
		
	public:
		void response( std::size_t _id ) override
		{
			m_adapter->start( _id );
		}

	protected:
		AdapterPtr m_adapter;
	};
	//////////////////////////////////////////////////////////////////////////
	void Adapter::connectSuccessful( const Proxy_GridManagerPtr & _gridManager )
	{
		_gridManager->addAdapter( m_name, new AdapterGridRegistrationResponse( this ) );		
	}
	//////////////////////////////////////////////////////////////////////////
	void Adapter::connectFailed()
	{
		
	}
}