#	include "pch.hpp"
#	include "Adapter.hpp"

#	include "AdapterSession.hpp"
#	include "AdapterConnection.hpp"

#	include "Servant.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Adapter::Adapter( const std::string & _name, const boost::asio::ip::tcp::endpoint & _endpoint )
		: Host(_endpoint)
		, m_name(_name)
		, m_id(0)
	{
		m_gridConnection = new GridConnection( m_service, this );
		m_connectionCache = new ConnectionCache( this );
	}
	//////////////////////////////////////////////////////////////////////////
	void Adapter::initialize( const boost::asio::ip::tcp::endpoint & _grid )
	{
		m_gridConnection->registerAdapter( _grid, m_name );
	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t Adapter::addServant( const ServantPtr & _servant )
	{
		std::size_t servantId = m_servants.size();

		m_servants.insert( std::make_pair( servantId, _servant ) );

		return servantId;
	}
	//////////////////////////////////////////////////////////////////////////
	void Adapter::dispatchMethod( std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, const AdapterSessionPtr & _session )
	{
		TMapServants::iterator it_find = m_servants.find( _servantId );

		if( it_find == m_servants.end() )
		{
			return;
		}

		const ServantPtr & servant = it_find->second;

		servant->callMethod( _methodId, _requestId, _session, m_connectionCache );
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
	void Adapter::connectSuccessful( std::size_t _enumeratorID )
	{
		m_id = _enumeratorID;

		this->accept();
	}
	//////////////////////////////////////////////////////////////////////////
	void Adapter::connectFailed()
	{
		
	}
}