#	pragma once

#	include <AxeUtil/Shared.hpp>

namespace Axe
{
	class ArchiveInvocation;
	class ArchiveDispatcher;

	class Exception;

	typedef AxeHandle<class Session> SessionPtr;
	typedef AxeHandle<class ConnectionCache> ConnectionCachePtr;
	typedef AxeHandle<class Proxy> ProxyPtr;
	
	class Servant
		: virtual public AxeUtil::Shared
	{
	public:
		Servant();

	public:
		void setServantId( std::size_t _servantId );
		std::size_t getServantId() const;
		
		void setHostId( std::size_t _hostId );
		std::size_t getHostId() const;

		ProxyPtr getProxy( const ConnectionCachePtr & _connectionCache );

	public:
		virtual void callMethod( std::size_t _id, std::size_t _requestId, const ArchiveDispatcher & _archive, const SessionPtr & _session );
		virtual void responseException( std::size_t _methodId, std::size_t _requestId, const ArchiveDispatcher & _archive, const SessionPtr & _session, const Exception & _ex );

	public:
		void write( ArchiveInvocation & _ar ) const;

	protected:
		std::size_t m_servantId;
		std::size_t m_hostId;
	};

	typedef AxeHandle<Servant> ServantPtr;
}