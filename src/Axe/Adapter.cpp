#	include "pch.hpp"
#	include "Adapter.hpp"

#	include "Communicator.hpp"
#	include "AdapterSession.hpp"
#	include "Servant.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Adapter::Adapter( boost::asio::io_service & _service, std::size_t _id, const boost::asio::ip::tcp::endpoint & _endpoint )
		: Host(_service, _endpoint)
		, m_id(_id)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Adapter::initialize()
	{
		this->run();
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

		servant->call_method( _methodId, _requestId, _session );
	}
	//////////////////////////////////////////////////////////////////////////
	SessionPtr Adapter::makeSession()
	{
		AdapterSessionPtr session = new AdapterSession( m_acceptor.get_io_service(), this );

		return session;
	}
}