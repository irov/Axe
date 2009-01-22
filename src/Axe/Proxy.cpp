#	include "pch.hpp"

#	include "Proxy.hpp"

#	include "ConnectionCache.hpp"

#	include "ArchiveWrite.hpp"
#	include "ArchiveRead.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Proxy::Proxy( std::size_t _servantId, const ConnectionPtr & _connection )
		: m_servantId(_servantId)
		, m_connection(_connection)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveWrite & Proxy::beginMessage( std::size_t _methodId, const ResponsePtr & _response )
	{
		ArchiveWrite & ar = m_connection->beginMessage( m_servantId, _methodId, _response );

		return ar;
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy::process()
	{
		m_connection->process();
	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t Proxy::getServantId() const
	{
		return m_servantId;
	}
	//////////////////////////////////////////////////////////////////////////
	const ConnectionPtr & Proxy::getConnection() const
	{
		return m_connection;
	}
	//////////////////////////////////////////////////////////////////////////
	const ConnectionPtr & makeProxyInfo( ArchiveRead & _ar, const ConnectionCachePtr & _connectionCache, std::size_t & _servantId )
	{
		_ar.read( _servantId );

		std::size_t endpointId;
		_ar.readSize( endpointId );

		const ConnectionPtr & connection = 
			_connectionCache->getConnection( endpointId );
		
		return connection;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( ArchiveWrite & ar, const ProxyPtr & _value )
	{
		std::size_t servantId = _value->getServantId();
		ar.write( servantId );

		const ConnectionPtr & connection = _value->getConnection();
		std::size_t endpointId = connection->getEndpointId();
		ar.writeSize( endpointId );
	}
}