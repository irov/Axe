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
		, m_hostId(0)
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
	void Servant::setHostId( std::size_t _hostId )
	{
		m_hostId = _hostId;
	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t Servant::getHostId() const
	{
		return m_hostId;
	}
	//////////////////////////////////////////////////////////////////////////
	ProxyPtr Servant::getProxy( const ConnectionCachePtr & _connectionCache )
	{
		const ConnectionPtr & cn = _connectionCache->getConnection( m_hostId );

		return new Proxy( m_servantId, cn );
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant::write( ArchiveWrite & _ar ) const
	{
		_ar.write( m_servantId );
		_ar.write( m_hostId );
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant::read( ArchiveRead & _ar )
	{
		_ar.read( m_servantId );
		_ar.read( m_hostId );
	}
}