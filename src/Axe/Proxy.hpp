#	pragma once

#	include "Shared.hpp"

#	include "Connection.hpp"

namespace Axe
{
	typedef AxeHandle<class ConnectionCache> ConnectionCachePtr;
	typedef AxeHandle<class Response> ResponsePtr;

	class ArchiveRead;
	class ArchiveWrite;

	class Proxy
		: virtual public Shared
	{
	public:
		Proxy( std::size_t _servantId, const ConnectionPtr & _connection );

	public:
		ArchiveWrite & beginMessage( std::size_t _methodId, const ResponsePtr & _response );
		void processMessage();

	public:
		std::size_t getServantId() const;
		const ConnectionPtr & getConnection() const;

	protected:
		std::size_t m_servantId;
		ConnectionPtr m_connection;
	};

	typedef AxeHandle<Proxy> ProxyPtr;

	template<class T>
	inline T uncheckedCast( const ProxyPtr & _proxy )
	{
		std::size_t servantId = _proxy->getServantId();
		const ConnectionPtr & connection = _proxy->getConnection();

		typedef typename T::element_type element_type;

		return new element_type( servantId, connection );
	}

	const ConnectionPtr & makeProxyInfo( ArchiveRead & ar, const ConnectionCachePtr & _connectionCache, std::size_t & servantId );

	template<class T>
	T makeProxy( ArchiveRead & _ar, const ConnectionCachePtr & _connectionCache )
	{
		std::size_t servantId;

		const ConnectionPtr & connection = 
			makeProxyInfo( _ar, _connectionCache, servantId );

		typedef typename T::element_type El;

		return new El( servantId, connection );
	}

	void operator << ( ArchiveWrite & ar, const ProxyPtr & _value );	
}