#	include "pch.hpp"

#	include <Axe/Proxy.hpp>

#	include <Axe/ConnectionCache.hpp>
#	include <Axe/ProxyHostProvider.hpp>

#	include <Axe/ArchiveInvocation.hpp>
#	include <Axe/ArchiveDispatcher.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Proxy::Proxy( std::size_t _servantId, const ProxyHostProviderPtr & _hostProvider )
		: m_servantId(_servantId)
		, m_hostProvider(_hostProvider)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveInvocation & Proxy::beginMessage( std::size_t _methodId, const ResponsePtr & _response )
	{
		const ConnectionPtr & connection = m_hostProvider->getConnection();
		ArchiveInvocation & ar = connection->beginMessage( m_servantId, _methodId, _response );

		return ar;
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy::processMessage()
	{
		const ConnectionPtr & connection = m_hostProvider->getConnection();
		connection->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t Proxy::getServantId() const
	{
		return m_servantId;
	}
	//////////////////////////////////////////////////////////////////////////
	const ProxyHostProviderPtr & Proxy::getProxyHostProvider() const
	{
		return m_hostProvider;
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy::write( ArchiveInvocation & _ar ) const
	{
		_ar << m_servantId;

		const ConnectionPtr & connection = m_hostProvider->getConnection();
		std::size_t hostId = connection->getHostId();
		_ar.writeSize( hostId );
	}
	//////////////////////////////////////////////////////////////////////////
	const ProxyHostProviderPtr & getProxyHostProvider( ArchiveDispatcher & _ar, std::size_t & _servantId )
	{
		_ar.read( _servantId );

		std::size_t hostId;
		_ar.readSize( hostId );

		const ConnectionCachePtr & connectionCache = _ar.getConnectionCache();

		const ProxyHostProviderPtr & provider = 
			connectionCache->getProxyHostProvider( _servantId, hostId );

		return provider;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( ArchiveInvocation & _ar, const ProxyPtr & _value )
	{
		_value->write(_ar);
	}
}