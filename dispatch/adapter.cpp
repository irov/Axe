#	include "pch.hpp"
#	include "adapter.hpp"

#	include "communicator.hpp"
#	include "adapter_session.hpp"
#	include "servant_base.hpp"

adapter::adapter( communicator * _cm, std::size_t _id, const boost::asio::ip::tcp::endpoint & _endpoint )
: host(_cm->get_service(), _endpoint)
, m_communicator(_cm)
, m_id(_id)
{
}

void adapter::initialize()
{
	this->run();
}

std::size_t adapter::add_servant( servant_base * _servant )
{
	std::size_t servantId = m_servants.size();

	m_servants.insert( std::make_pair( servantId, _servant ) );

	return servantId;
}

void adapter::dispatch_method( std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, adapter_session * _sn )
{
	TMapServants::iterator it_find = m_servants.find( _servantId );

	if( it_find == m_servants.end() )
	{
		return;
	}

	servant_base * servant = it_find->second;

	servant->call_method( _methodId, _requestId, _sn );
}

session * adapter::make_session()
{
	adapter_session * sn = new adapter_session( m_acceptor.get_io_service(), this );

	return sn;
}
