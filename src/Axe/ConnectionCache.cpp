#	include "pch.hpp"

#	include <Axe/ConnectionCache.hpp>

#	include <Axe/Connection.hpp>
#	include <Axe/ServantConnection.hpp>
#	include <Axe/ProxyConnectionProvider.hpp>

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
		TMapAdapterConnections::const_iterator it_found = m_adapterConnections.find( _adapterId );

		if( it_found == m_adapterConnections.end() )
		{
			ConnectionPtr connection = m_provider->createAdapterConnection( _adapterId );

			it_found = m_adapterConnections.insert( std::make_pair(_adapterId, connection) ).first;
		}

		return it_found->second;
	}
	//////////////////////////////////////////////////////////////////////////
	void ConnectionCache::addServantConnection( const std::string & _name, const ConnectionPtr & _connection )
	{
		m_servantConnections.insert( std::make_pair(_name, _connection) );
	}
	//////////////////////////////////////////////////////////////////////////
	const ProxyConnectionProviderPtr & ConnectionCache::getProxyServantProvider( const std::string & _name, const boost::asio::ip::tcp::endpoint & _endpoint )
	{
		TMapProxyServantProviders::const_iterator it_found = m_proxyServantProviders.find( _name );

		if( it_found == m_proxyServantProviders.end() )
		{
			const ConnectionPtr & connection = this->getServantConnection( _name, _endpoint );
			
			ProxyConnectionProviderPtr provider = new ProxyConnectionProvider( connection );

			it_found = m_proxyServantProviders.insert( std::make_pair(_name, provider) ).first;
		}

		return it_found->second;
	}
	//////////////////////////////////////////////////////////////////////////
	const ConnectionPtr & ConnectionCache::getServantConnection( const std::string & _name, const boost::asio::ip::tcp::endpoint & _endpoint )
	{
		TMapServantConnections::const_iterator it_found = m_servantConnections.find( _name );

		if( it_found == m_servantConnections.end() )
		{
			ConnectionPtr connection = m_provider->createServantConnection( _name, _endpoint );

			it_found = m_servantConnections.insert( std::make_pair(_name, connection) ).first;
		}

		return it_found->second;
	}
	//////////////////////////////////////////////////////////////////////////
	void ConnectionCache::addRouterConnection( const boost::asio::ip::tcp::endpoint & _endpoint, const ConnectionPtr & _connection )
	{
		m_routerConnections.insert( std::make_pair(_endpoint, _connection) );
	}
	//////////////////////////////////////////////////////////////////////////
	const ConnectionPtr & ConnectionCache::getRouterConnection( const boost::asio::ip::tcp::endpoint & _endpoint )
	{
		TMapRouterConnections::const_iterator it_found = m_routerConnections.find( _endpoint );

		if( it_found == m_routerConnections.end() )
		{
			ConnectionPtr connection = m_provider->createRouterConnection( _endpoint );

			it_found = m_routerConnections.insert( std::make_pair(_endpoint, connection) ).first;
		}

		return it_found->second;
	}
	//////////////////////////////////////////////////////////////////////////
	const ProxyConnectionProviderPtr & ConnectionCache::getProxyAdapterProvider( std::size_t _servantId, std::size_t _adapterId )
	{
		TMapProxyAdapterProviders::const_iterator it_found = m_proxyAdapterProviders.find( _servantId );

		if( it_found == m_proxyAdapterProviders.end() )
		{
			const ConnectionPtr & connection = this->getAdapterConnection( _adapterId );

			ProxyConnectionProviderPtr provider = new ProxyConnectionProvider( connection );

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