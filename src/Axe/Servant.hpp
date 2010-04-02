#	pragma once

#	include <AxeUtil/Shared.hpp>

namespace Axe
{
	class ArchiveInvocation;
	class ArchiveDispatcher;

	class Exception;

	typedef AxeHandle<class Session> SessionPtr;
	typedef AxeHandle<class Communicator> CommunicatorPtr;
	typedef AxeHandle<class ConnectionCache> ConnectionCachePtr;
	typedef AxeHandle<class Proxy> ProxyPtr;

	typedef AxeHandle<class Bellhop_Servant_destroy> Bellhop_Servant_destroyPtr;
	
	class Servant
		: virtual public AxeUtil::Shared
	{
	public:
		Servant();

	public:
		void setServantId( std::size_t _servantId );
		std::size_t getServantId() const;
		
		void setAdapterId( std::size_t _adapterId );
		std::size_t getAdapterId() const;

	public:
		ProxyPtr getProxy( const ConnectionCachePtr & _connectionCache );

	protected:
		virtual void destroy_async( const Bellhop_Servant_destroyPtr & _cb );

	public:
		void dispatchMethod( std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const SessionPtr & _session );

	public:
		virtual void callMethod( std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const SessionPtr & _session );
		virtual void responseException( std::size_t _methodId, std::size_t _requestId, const SessionPtr & _session, const Exception & _ex );

	public:
		bool restore( ArchiveDispatcher & _ar, const boost::property_tree::ptree & _pr );
		void evict( ArchiveInvocation & _aw );

	protected:
		virtual void _restore( ArchiveDispatcher & _ar );
		virtual void _evict( ArchiveInvocation & _aw );

		virtual bool onRestore( const boost::property_tree::ptree & _pr );
		virtual void onEvict();

	protected:
		std::size_t m_servantId;
		std::size_t m_adapterId;
	};

	typedef AxeHandle<Servant> ServantPtr;
}