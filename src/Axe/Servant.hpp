#	pragma once

#	include "Shared.hpp"

namespace Axe
{
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
		
		void setEndpointId( std::size_t _servantId );
		std::size_t getEndpointId() const;

		ProxyPtr getProxy( const ConnectionCachePtr & _connectionCache );

	public:
		virtual void callMethod( std::size_t _id, std::size_t _requestId, const SessionPtr & _session, const ConnectionCachePtr & _connectionCache ) = 0;

	protected:
		std::size_t m_servantId;
		std::size_t m_endpointId;
	};

	typedef AxeHandle<Servant> ServantPtr;

	void operator << ( ArchiveWrite & ar, const ServantPtr & _value );
}