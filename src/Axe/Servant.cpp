#	include "pch.hpp"

#	include <Axe/Servant.hpp>
#	include <Axe/Proxy.hpp>
#	include <Axe/Exception.hpp>

#	include <Axe/ArchiveInvocation.hpp>


#	include <Axe/ConnectionCache.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Servant::Servant()
		: m_servantId(-1)
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
	void Servant::setHost( const HostPtr & _host )
	{
		m_host = _host;
	}
	//////////////////////////////////////////////////////////////////////////
	const HostPtr & Servant::getHost() const
	{
		return m_host;
	}
	//////////////////////////////////////////////////////////////////////////
	ProxyPtr Servant::getProxy( const ConnectionCachePtr & _connectionCache )
	{
		std::size_t hostId = m_host->getHostId();

		const ConnectionPtr & cn = _connectionCache->getConnection( hostId );

		return new Proxy( m_servantId, cn );
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant::write( ArchiveInvocation & _ar ) const
	{
		_ar << m_servantId;

		std::size_t hostId = m_host->getHostId();
		_ar << hostId;
	}
}