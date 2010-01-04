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
		const ConnectionPtr & cn = _connectionCache->getConnection( m_hostId );

		return new Proxy( m_servantId, cn );
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant::write( ArchiveInvocation & _ar ) const
	{
		_ar << m_servantId;
		_ar << m_hostId;
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
	void operator << ( ArchiveInvocation & _ar, const ServantPtr & _value )
	{
		_value->write(_ar);
	}
}