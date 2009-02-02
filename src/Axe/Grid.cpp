#	include "pch.hpp"

#	include "Grid.hpp"
#	include "GridSession.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Grid::Grid( const boost::asio::ip::tcp::endpoint & _endpoint )
		: Host( _endpoint)
	{

	}
	//////////////////////////////////////////////////////////////////////////
	void Grid::initialize()
	{
		this->run();
	}
	//////////////////////////////////////////////////////////////////////////
	SessionPtr Grid::makeSession()
	{
		GridSessionPtr session = new GridSession( m_service, this );

		return session;
	}
	//////////////////////////////////////////////////////////////////////////
	void Grid::dispatchMethod( std::size_t _sizeArgs, std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, std::size_t _endpointId, const RouterSessionPtr & _session )
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
