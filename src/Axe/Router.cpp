#	include "pch.hpp"

#	include "Router.hpp"
#	include "RouterResponse.hpp"
#	include "RouterSession.hpp"

#	include "Connection.hpp"
#	include "ArchiveWrite.hpp"
#	include "ArchiveRead.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Router::Router( const boost::asio::ip::tcp::endpoint & _endpoint )
		: Host( _endpoint)
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
		RouterSessionPtr session = new RouterSession( m_service, this );

		return session;
	}
	//////////////////////////////////////////////////////////////////////////
	void Router::dispatchMethod( std::size_t _sizeArgs, std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, std::size_t _endpointId, const RouterSessionPtr & _session )
	{
		TMapRouming::iterator it_find = m_rouming.find( _endpointId );

		if( it_find == m_rouming.end() )
		{
			return;
		}

		const ConnectionPtr & cn = it_find->second;

		ArchiveWrite & write = cn->beginMessage( _servantId, _methodId, new RouterResponse( _requestId, _session ) );

		ArchiveRead & read = _session->getArchiveRead();

		const Archive::value_type * args_buff = read.selectBuffer( _sizeArgs );

		write.writeArchive( args_buff, _sizeArgs );

		cn->process();
	}
}
