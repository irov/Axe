#	pragma once

#	include <AxeUtil/Shared.hpp>

#	include <Axe/Connection.hpp>

namespace Axe
{
	typedef AxeHandle<class ConnectionCache> ConnectionCachePtr;
	typedef AxeHandle<class Response> ResponsePtr;

	class ArchiveDispatcher;
	class ArchiveInvocation;

	class Proxy
		: virtual public AxeUtil::Shared
	{
	public:
		Proxy( std::size_t _servantId, const ConnectionPtr & _connection );

	public:
		ArchiveInvocation & beginMessage( std::size_t _methodId, const ResponsePtr & _response );
		void processMessage();

	public:
		std::size_t getServantId() const;
		const ConnectionPtr & getConnection() const;

	public:
		void write( ArchiveInvocation & _ar ) const;

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

	const ConnectionPtr & makeProxyInfo( ArchiveDispatcher & ar, std::size_t & servantId );

	template<class T>
	T makeProxy( ArchiveDispatcher & _ar )
	{
		std::size_t servantId;

		const ConnectionPtr & connection = 
			makeProxyInfo( _ar, servantId );

		typedef typename T::element_type El;

		return new El( servantId, connection );
	}
}