#	include "pch.hpp"

#	include "ServantConnection.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	ServantConnection::ServantConnection( const SocketPtr & _socket, const ConnectionCachePtr & _connectionCache, const std::string & _uniqueId )
		: Connection( _socket, _connectionCache )
		, m_uniqueId(_uniqueId)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveInvocation & beginMessage( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response )
	{

	}
}