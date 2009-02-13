#	include "pch.hpp"
#	include "Adapter.hpp"

#	include "AdapterSession.hpp"
#	include "AdapterConnection.hpp"

#	include "Servant.hpp"

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
		m_gridConnection->registerAdapter( _grid, m_name );
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
	void Adapter::connectSuccessful( std::size_t _endpointId )
	{
		this->refreshServantEndpoint( _endpointId );

		this->accept();
	}
	//////////////////////////////////////////////////////////////////////////
	void Adapter::connectFailed()
	{
		
	}
}