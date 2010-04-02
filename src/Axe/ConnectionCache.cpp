#	include "pch.hpp"

#	include <Axe/ConnectionCache.hpp>

#	include <Axe/Connection.hpp>
#	include <Axe/ProxyAdapterProvider.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	ConnectionCache::ConnectionCache( const ConnectionProviderPtr & _provider )
		: m_provider(_provider)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void ConnectionCache::addAdapterConnection( std::size_t _adapterId, const ConnectionPtr & _connection )
	{
		m_adapterConnections.insert( std::make_pair(_adapterId, _connection) );
	}
	//////////////////////////////////////////////////////////////////////////
	const ConnectionPtr & ConnectionCache::getAdapterConnection( std::size_t _adapterId )
	{
		TMapConnections::const_iterator it_found = m_adapterConnections.find( _adapterId );

		if( it_found == m_adapterConnections.end() )
		{
			ConnectionPtr connection = m_provider->createConnection( _adapterId );

			it_found = m_adapterConnections.insert( std::make_pair(_adapterId, connection) ).first;
		}

		return it_found->second;
	}
	//////////////////////////////////////////////////////////////////////////
	const ProxyAdapterProviderPtr & ConnectionCache::getProxyAdapterProvider( std::size_t _servantId, std::size_t _adapterId )
	{
		TMapProxyAdapterProviders::const_iterator it_found = m_proxyAdapterProviders.find( _servantId );

		if( it_found == m_proxyAdapterProviders.end() )
		{
			const ConnectionPtr & connection = this->getAdapterConnection( _adapterId );

			ProxyAdapterProviderPtr provider = new ProxyAdapterProvider( connection );

			it_found = m_proxyAdapterProviders.insert( std::make_pair(_servantId, provider) ).first;
		}

		return it_found->second;
	}
	//////////////////////////////////////////////////////////////////////////
	void ConnectionCache::relocateProxy( std::size_t _servantId, std::size_t _adapterId )
	{
		TMapProxyAdapterProviders::iterator it_found = m_proxyAdapterProviders.find( _servantId );

		if( it_found == m_proxyAdapterProviders.end() )
		{
			return;
		}

		const ConnectionPtr & connection = this->getAdapterConnection( _adapterId );

		it_found->second->setConnection( connection );
	}
}