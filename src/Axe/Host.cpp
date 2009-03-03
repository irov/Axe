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
		, m_hostId(0)
	{
		m_connectionCache = new ConnectionCache( this );
	}
	//////////////////////////////////////////////////////////////////////////
	ProxyPtr Host::addServant( const ServantPtr & _servant )
	{
		std::size_t servantId = _servant->getServantId();

		ProxyPtr proxy = this->addServantByID( _servant, servantId );

		return proxy;
	}
	//////////////////////////////////////////////////////////////////////////
	ProxyPtr Host::addServantUnique( const ServantPtr & _servant )
	{
		std::size_t servantId = 0;

		TMapServants::reverse_iterator it_back = m_servants.rbegin();

		if( it_back != m_servants.rend() )
		{
			servantId = it_back->first + 1;
		}

		ProxyPtr proxy = this->addServantByID( _servant, servantId );

		return proxy;
	}
	//////////////////////////////////////////////////////////////////////////
	ProxyPtr Host::addServantByID( const ServantPtr & _servant, std::size_t _servantId )
	{
		_servant->setHost( this );

		bool inserted = m_servants.insert( std::make_pair( _servantId, _servant ) ).second;

		if( inserted == false )
		{
			printf("Host::addServant host '%d' already exist servant '%d'\n"
				, m_hostId
				, _servantId 
				);
		}

		const ConnectionPtr & cn = m_connectionCache->getConnection( m_hostId );

		ProxyPtr proxy = new Proxy( _servantId, cn );

		return proxy;
	}
	//////////////////////////////////////////////////////////////////////////
	void Host::setHostId( std::size_t _hostId )
	{
		m_hostId = _hostId;
	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t Host::getHostId() const
	{
		return m_hostId;
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

		servant->callMethod( _methodId, _requestId, _session );
	}
}