#	include "pch.hpp"

#	include <Axe/Connection.hpp>
#	include <Axe/ConnectionCache.hpp>
#	include <Axe/ProxyHostProvider.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	ConnectionCache::ConnectionCache( const ConnectionProviderPtr & _provider )
		: m_provider(_provider)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void ConnectionCache::addConnection( std::size_t _hostId, const ConnectionPtr & _connection )
	{
		m_connections.insert( std::make_pair(_hostId, _connection) );
	}
	//////////////////////////////////////////////////////////////////////////
	const ConnectionPtr & ConnectionCache::getConnection( std::size_t _hostId )
	{
		TMapConnections::const_iterator it_found = m_connections.find( _hostId );

		if( it_found == m_connections.end() )
		{
			ConnectionPtr connection = m_provider->createConnection( _hostId );

			it_found = m_connections.insert( std::make_pair(_hostId, connection) ).first;
		}

		return it_found->second;
	}
	//////////////////////////////////////////////////////////////////////////
	const ProxyHostProviderPtr & ConnectionCache::getProxyHostProvider( std::size_t _servantId, std::size_t _hostId )
	{
		TMapProxyHostProviders::iterator it_found = m_proxyHostProviders.find( _servantId );

		if( it_found == m_proxyHostProviders.end() )
		{
			const ConnectionPtr & connection = this->getConnection( _hostId );

			ProxyHostProviderPtr proxyHostProvider = new ProxyHostProvider( connection );

			it_found = m_proxyHostProviders.insert( std::make_pair(_servantId, proxyHostProvider) ).first;
		}

		return it_found->second;
	}
}