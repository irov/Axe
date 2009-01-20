#	include "pch.hpp"

#	include "RouterConnection.hpp"

#	include "Response.hpp"

#	include "ArchiveWrite.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	RouterConnection::RouterConnection( boost::asio::io_service & _service )
		: AdapterConnection( _service )
	{

	}
	//////////////////////////////////////////////////////////////////////////
	void RouterConnection::dispatchMessage( std::size_t _size )
	{
		std::size_t responseId;
		m_streamIn->readSize( responseId );

		TMapResponse::iterator it_found = m_dispatch.find( responseId );

		const ResponsePtr & response = it_found->second;

		response->responseCall( m_streamIn );

		m_streamIn->clear();
	}
	//////////////////////////////////////////////////////////////////////////
	const ConnectionPtr & RouterConnection::getConnection( std::size_t _id )
	{
		TMapRouterConnections::iterator it_found = m_connections.find( _id );

		if( it_found == m_connections.end() )
		{
			RouterProxyConnection cn = new RouterConnectionPtr( this, _id );

			it_found = m_connections.insert( std::make_pair( _id, cn ) ).first;
		}

		return it_found->second;
	}
}