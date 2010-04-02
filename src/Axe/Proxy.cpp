#	include "pch.hpp"

#	include <Axe/Proxy.hpp>

#	include <Axe/ConnectionCache.hpp>
#	include <Axe/ProxyAdapterProvider.hpp>

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
	Proxy::Proxy( std::size_t _servantId, const ProxyAdapterProviderPtr & _adapterProvider )
		: m_servantId(_servantId)
		, m_adapterProvider(_adapterProvider)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t Proxy::getServantId() const
	{
		return m_servantId;
	}
	//////////////////////////////////////////////////////////////////////////
	const ProxyAdapterProviderPtr & Proxy::getProxyAdapterProvider() const
	{
		return m_adapterProvider;
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveInvocation & Proxy::beginMessage( std::size_t _methodId, const ResponsePtr & _response )
	{
		const ConnectionPtr & connection = m_adapterProvider->getConnection();
		ArchiveInvocation & ar = connection->beginMessage( m_servantId, _methodId, _response );

		return ar;
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy::processMessage()
	{
		const ConnectionPtr & connection = m_adapterProvider->getConnection();

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

		const ConnectionPtr & connection = m_adapterProvider->getConnection();
		
		std::size_t adapterId = connection->getAdapterId();

		_ar.writeSize( adapterId );
	}
	//////////////////////////////////////////////////////////////////////////
	const ProxyAdapterProviderPtr & makeProxyAdapterProvider( ArchiveDispatcher & _ar, std::size_t & _servantId )
	{
		_ar.read( _servantId );

		std::size_t adapterId;
		_ar.readSize( adapterId );

		const ConnectionCachePtr & connectionCache = _ar.getConnectionCache();

		const ProxyAdapterProviderPtr & provider = 
			connectionCache->getProxyAdapterProvider( _servantId, adapterId );

		return provider;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator >> ( ArchiveDispatcher & _ar, ProxyPtr & _value )
	{
		ProxyPtr self = makeProxy<ProxyPtr>( _ar );

		_value.swap( self );
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( ArchiveInvocation & _ar, const ProxyPtr & _value )
	{
		_value->write(_ar);
	}
}