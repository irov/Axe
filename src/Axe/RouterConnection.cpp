#	include "pch.hpp"

#	include "RouterConnection.hpp"
#	include "RouterProxyConnection.hpp"

#	include "Response.hpp"

#	include "ArchiveRead.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	RouterConnection::RouterConnection( boost::asio::io_service & _service )
		: AdapterConnection( _service )
	{

	}
	//////////////////////////////////////////////////////////////////////////
	void RouterConnection::dispatchMessage( ArchiveRead & _read, std::size_t _size )
	{
		std::size_t responseId;
		_read.readSize( responseId );

		TMapResponse::iterator it_found = m_dispatch.find( responseId );

		const ResponsePtr & response = it_found->second;

		response->responseCall( _read );

		_read.clear();
	}
	//////////////////////////////////////////////////////////////////////////
	const RouterProxyConnectionPtr & RouterConnection::getConnection( std::size_t _id )
	{
		TMapRouterConnections::iterator it_found = m_connections.find( _id );

		if( it_found == m_connections.end() )
		{
			RouterProxyConnectionPtr cn = new RouterProxyConnection( this, _id );

			it_found = m_connections.insert( std::make_pair( _id, cn ) ).first;
		}

		return it_found->second;
	}
}