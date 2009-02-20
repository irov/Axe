#	include "pch.hpp"
#	include "Host.hpp"

#	include "AdapterSession.hpp"
#	include "AdapterConnection.hpp"

#	include "Servant.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Host::Host( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name )
		: Service(_endpoint, _name)
		, m_endpointId(0)
	{
		m_connectionCache = new ConnectionCache( this );
	}
	//////////////////////////////////////////////////////////////////////////
	ProxyPtr Host::addServant( const ServantPtr & _servant )
	{
		std::size_t servantId = _servant->getServantId();

		_servant->setEndpointId( m_endpointId );

		m_servants.insert( std::make_pair( servantId, _servant ) );

		const ConnectionPtr & cn = m_connectionCache->getConnection( m_endpointId );

		ProxyPtr proxy = new Proxy( servantId, cn );

		return proxy;
	}
	//////////////////////////////////////////////////////////////////////////
	void Host::setEndpointId( std::size_t _endpointId )
	{
		m_endpointId = _endpointId;
	}
	//////////////////////////////////////////////////////////////////////////
	void Host::refreshServantEndpoint( std::size_t _endpointId )
	{
		setEndpointId( _endpointId );

		for( TMapServants::iterator
			it = m_servants.begin(),
			it_end = m_servants.end();
		it != it_end;
		++it )
		{
			it->second->setEndpointId( m_endpointId );
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void Host::dispatchMethod( std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, const SessionPtr & _session )
	{
		TMapServants::iterator it_find = m_servants.find( _servantId );

		if( it_find == m_servants.end() )
		{
			return;
		}

		const ServantPtr & servant = it_find->second;

		servant->callMethod( _methodId, _requestId, _session, m_connectionCache );
	}
}