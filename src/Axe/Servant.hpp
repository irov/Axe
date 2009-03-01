#	pragma once

#	include "Shared.hpp"
#	include "Host.hpp"

namespace Axe
{
	class ArchiveRead;
	class ArchiveWrite;

	typedef AxeHandle<class Session> SessionPtr;
	
	typedef AxeHandle<class Proxy> ProxyPtr;
	typedef AxeHandle<class ConnectionCache> ConnectionCachePtr;
	
	class Servant
		: virtual public Shared
	{
	public:
		Servant();

	public:
		void setServantId( std::size_t _servantId );
		std::size_t getServantId() const;
		
		void setHost( const HostPtr & _host );
		const HostPtr & getHost() const;

		ProxyPtr getProxy( const ConnectionCachePtr & _connectionCache );

	public:
		virtual void callMethod( std::size_t _id, std::size_t _requestId, const SessionPtr & _session, const ConnectionCachePtr & _connectionCache ) = 0;

	public:
		void write( ArchiveWrite & _ar ) const;

	protected:
		std::size_t m_servantId;
		HostPtr m_host;
	};

	typedef AxeHandle<Servant> ServantPtr;
}