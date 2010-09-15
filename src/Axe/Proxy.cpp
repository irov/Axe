#	include "pch.hpp"

#	include <Axe/Proxy.hpp>

#	include <Axe/ConnectionCache.hpp>
#	include <Axe/ProxyConnectionProvider.hpp>

#	include <Axe/ArchiveInvocation.hpp>
#	include <Axe/ArchiveDispatcher.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	void Response_Servant_destroy::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		this->response();
	}
	//////////////////////////////////////////////////////////////////////////
	Proxy::Proxy( std::size_t _servantId, const ProxyConnectionProviderPtr & _adapterProvider )
		: m_servantId(_servantId)
		, m_connectionProvider(_adapterProvider)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t Proxy::getServantId() const
	{
		return m_servantId;
	}
	//////////////////////////////////////////////////////////////////////////
	const ProxyConnectionProviderPtr & Proxy::getConnectionProvider() const
	{
		return m_connectionProvider;
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveInvocation & Proxy::beginMessage( std::size_t _methodId, const ResponsePtr & _response )
	{
		const ConnectionPtr & connection = m_connectionProvider->getConnection();
		ArchiveInvocation & ar = connection->beginMessage( m_servantId, _methodId, _response );

		return ar;
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy::processMessage()
	{
		const ConnectionPtr & connection = m_connectionProvider->getConnection();

		connection->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy::destroy_async( const Response_Servant_destroyPtr & _response )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 1, _response );
		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy::write( ArchiveInvocation & _ar ) const
	{
		_ar << m_servantId;

		const ConnectionPtr & connection = m_connectionProvider->getConnection();
		
		connection->write( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	const ProxyConnectionProviderPtr & makeProxyConnectionProvider( ArchiveDispatcher & _ar, std::size_t & _servantId )
	{
		_ar.read( _servantId );

		std::size_t adapterId;
		_ar.readSize( adapterId );

		const ConnectionCachePtr & connectionCache = _ar.getConnectionCache();

		const ProxyConnectionProviderPtr & provider = 
			connectionCache->getProxyAdapterProvider( _servantId, adapterId );

		return provider;
	}
}