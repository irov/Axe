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
	void Proxy::processMessage()
	{
		m_connection->processMessage();
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
	void Proxy::write( ArchiveWrite & _ar ) const
	{
		_ar.write( m_servantId );

		const ConnectionPtr & connection = this->getConnection();
		std::size_t endpointId = connection->getHostId();
		_ar.writeSize( endpointId );
	}
	//////////////////////////////////////////////////////////////////////////
	const ConnectionPtr & makeProxyInfo( ArchiveRead & _ar, std::size_t & _servantId )
	{
		_ar.read( _servantId );

		std::size_t endpointId;
		_ar.readSize( endpointId );

		const ConnectionCachePtr & connectionCache = _ar.getConnectionCache();

		const ConnectionPtr & connection = 
			connectionCache->getConnection( endpointId );

		return connection;
	}
}