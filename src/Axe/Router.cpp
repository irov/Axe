#	include "pch.hpp"

#	include "Router.hpp"
#	include "RouterSession.hpp"

#	include "Connection.hpp"
#	include "Stream.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Router::Router( boost::asio::io_service & _service, const boost::asio::ip::tcp::endpoint & _endpoint )
		: Host(_service, _endpoint)
	{

	}
	//////////////////////////////////////////////////////////////////////////
	void Router::initialize()
	{
		this->run();
	}
	//////////////////////////////////////////////////////////////////////////
	SessionPtr Router::makeSession()
	{
		RouterSessionPtr session = new RouterSession( m_acceptor.get_io_service(), this );

		return session;
	}
	//////////////////////////////////////////////////////////////////////////
	void Router::dispatchMethod( std::size_t _sizeArgs, std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, std::size_t _endpointId, const RouterSession & _session )
	{
		TMapRouming::iterator it_find = m_rouming.find( _endpointId );

		if( it_find == m_rouming.end() )
		{
			return;
		}

		const ConnectionPtr & cn = it_find->second;

		ArchiveWrite & write = cn->beginMessage( _servantId, _methodId, new RouterResponse( _requestId, _session ) );

		ArchiveRead & read = _session->getArchiveRead();

		TBlobject::value_type * args_buff = read->selectBuffer( _sizeArgs );

		write->writeArchive( args_buff, _sizeArgs );

		cn->procces();
	}
}
