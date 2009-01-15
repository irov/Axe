#	include "pch.hpp"

#	include "router.hpp"

#	include "router_session.hpp"

#	include "connection.hpp"
#	include "stream.hpp"

router_response::router_response( std::size_t _requestId, router_session * _sn )
: m_requestId(_requestId)
, m_session(_sn)
{

}

void router_response::response_call( stream_read * _cn )
{
	//_cn->
}


router::router( boost::asio::io_service & _service, const boost::asio::ip::tcp::endpoint & _endpoint )
: host(_service, _endpoint)
{

}

void router::initialize()
{
	this->run();
}

session * router::make_session()
{
	router_session * sn = new router_session( m_acceptor.get_io_service(), this );

	return sn;
}

void router::dispatch_method( std::size_t _sizeArgs, std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, std::size_t _endpointId, router_session * _sn )
{
	TMapRouming::iterator it_find = m_rouming.find( _endpointId );

	if( it_find == m_rouming.end() )
	{
		return;
	}

	connection * cn = it_find->second;

	stream_write * write = cn->begin_message( _servantId, _methodId, new router_response( _requestId, _sn ) );

	stream_read * read = _sn->get_streamIn();

	TBlobject::value_type * args_buff = read->select_buff( _sizeArgs );

	write->write_buff( args_buff, _sizeArgs );

	cn->procces();
}
