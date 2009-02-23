#	include "pch.hpp"

#	include "Servant.hpp"
#	include "Proxy.hpp"

#	include "ArchiveRead.hpp"
#	include "ArchiveWrite.hpp"


#	include "ConnectionCache.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Servant::Servant()
		: m_servantId(0)
		, m_endpointId(0)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant::setServantId( std::size_t _servantId )
	{
		m_servantId = _servantId;
	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t Servant::getServantId() const
	{
		return m_servantId;
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant::setEndpointId( std::size_t _endpointId )
	{
		m_endpointId = _endpointId;
	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t Servant::getEndpointId() const
	{
		return m_endpointId;
	}
	//////////////////////////////////////////////////////////////////////////
	ProxyPtr Servant::getProxy( const ConnectionCachePtr & _connectionCache )
	{
		const ConnectionPtr & cn = _connectionCache->getConnection( m_endpointId );

		return new Proxy( m_servantId, cn );
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant::write( ArchiveWrite & _ar ) const
	{
		_ar.write( m_servantId );
		_ar.write( m_endpointId );
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant::read( ArchiveRead & _ar )
	{
		_ar.read( m_servantId );
		_ar.read( m_endpointId );
	}
}