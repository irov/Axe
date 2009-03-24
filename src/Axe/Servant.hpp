#	pragma once

#	include <AxeUtil/Shared.hpp>
#	include <Axe/Host.hpp>

namespace Axe
{
	class ArchiveRead;
	class ArchiveWrite;

	class Exception;

	typedef AxeHandle<class Session> SessionPtr;
	
	typedef AxeHandle<class Proxy> ProxyPtr;
	
	class Servant
		: virtual public AxeUtil::Shared
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
		virtual void callMethod( std::size_t _id, std::size_t _requestId, const SessionPtr & _session ) = 0;
		virtual void responseException( std::size_t _methodId, std::size_t _requestId, const SessionPtr & _session, const Exception & _ex ) = 0;

	public:
		void write( ArchiveWrite & _ar ) const;

	protected:
		std::size_t m_servantId;
		HostPtr m_host;
	};

	typedef AxeHandle<Servant> ServantPtr;
}