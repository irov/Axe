#	include "pch.hpp"

#	include <Axe/Servant.hpp>
#	include <Axe/Proxy.hpp>
#	include <Axe/Exception.hpp>

#	include <Axe/ArchiveInvocation.hpp>
#	include <Axe/ConnectionCache.hpp>
#	include <Axe/ProxyHostProvider.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Servant::Servant()
		: m_servantId(-1)
		, m_hostId(-1)
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
		const ProxyHostProviderPtr & provider = _connectionCache->getProxyHostProvider( m_servantId, m_hostId );

		return new Proxy( m_servantId, provider );
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant::callMethod( std::size_t _id, std::size_t _requestId, ArchiveDispatcher & _archive, const SessionPtr & _session )
	{
		//Empty
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant::responseException( std::size_t _methodId, std::size_t _requestId, const SessionPtr & _session, const Exception & _ex )
	{
		//Empty
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant::restore( ArchiveDispatcher & _ar )
	{
		this->_restore(_ar);
		this->onRestore();
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant::evict( ArchiveInvocation & _aw )
	{
		this->onEvict();
		this->_evict(_aw);
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant::_restore( ArchiveDispatcher & _ar )
	{
		//Empty
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant::_evict( ArchiveInvocation & _aw )
	{
		//Empty
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant::onRestore()
	{
		//Empty
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant::onEvict()
	{
		//Empty
	}
}