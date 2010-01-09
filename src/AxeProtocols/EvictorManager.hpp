#	pragma once

#	include <Axe/Bellhop.hpp>
#	include <Axe/Servant.hpp>
#	include <Axe/Response.hpp>
#	include <Axe/Proxy.hpp>
#	include <Axe/Response.hpp>
#	include <Axe/Exception.hpp>

namespace Axe
{
	class ArchiveInvocation;
	class ArchiveDispatcher;
}

namespace Axe
{
	
	class EvictingNotFoundException
		: virtual public Axe::Exception
	{
	public:
		void rethrow() const override;
	
	public:
		std::size_t servantId;
	
	public:
		void write( Axe::ArchiveInvocation & _ar ) const override;
		void read( Axe::ArchiveDispatcher & _ar ) override;
	};
	
	typedef AxeHandle<EvictingNotFoundException> EvictingNotFoundExceptionPtr;
	
	
	class EvictingAlreadyRestored
		: virtual public Axe::Exception
	{
	public:
		void rethrow() const override;
	
	public:
		std::size_t servantId;
		std::size_t hostId;
	
	public:
		void write( Axe::ArchiveInvocation & _ar ) const override;
		void read( Axe::ArchiveDispatcher & _ar ) override;
	};
	
	typedef AxeHandle<EvictingAlreadyRestored> EvictingAlreadyRestoredPtr;
	
	
	typedef AxeHandle<class Bellhop_EvictorManager_set> Bellhop_EvictorManager_setPtr;
	typedef AxeHandle<class Bellhop_EvictorManager_get> Bellhop_EvictorManager_getPtr;
	
	class Servant_EvictorManager
		: virtual public Axe::Servant
	{
	public:
		virtual void set_async( const Bellhop_EvictorManager_setPtr & _cb, std::size_t _servantId, std::size_t _typeId, const AxeUtil::Archive & _ar ) = 0;
		virtual void get_async( const Bellhop_EvictorManager_getPtr & _cb, std::size_t _servantId, std::size_t _hostId ) = 0;
	
	public:
		void callMethod( std::size_t _methodId , std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session ) override;
		void responseException( std::size_t _methodId, std::size_t _requestId, const SessionPtr & _session, const Exception & _ex ) override;
	public:
		void writeExceptions_( std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
	};
	
	typedef AxeHandle<Servant_EvictorManager> Servant_EvictorManagerPtr;
	
	
	class Bellhop_EvictorManager_set
		: public Axe::Bellhop
	{
	public:
		Bellhop_EvictorManager_set( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_EvictorManagerPtr & _servant );
	
	public:
		void response();
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_EvictorManagerPtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_EvictorManager_set> Bellhop_EvictorManager_setPtr;
	class Bellhop_EvictorManager_get
		: public Axe::Bellhop
	{
	public:
		Bellhop_EvictorManager_get( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_EvictorManagerPtr & _servant );
	
	public:
		void response( const AxeUtil::Archive &, std::size_t _typeId );
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_EvictorManagerPtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_EvictorManager_get> Bellhop_EvictorManager_getPtr;
	
	//////////////////////////////////////////////////////////////////////////
	class Response_EvictorManager_set
		: public Axe::Response
	{
	protected:
		virtual void response() = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
		void exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_EvictorManager_set> Response_EvictorManager_setPtr;
	
	template<>
	class BindResponse<Response_EvictorManager_setPtr>
		: public Response_EvictorManager_set
	{
		typedef boost::function<void()> TBindResponse;
		typedef boost::function<void(const Axe::Exception &)> TBindException;
	
	public:
		BindResponse( const TBindResponse & _response, const TBindException & _exception );
	
	public:
		void response() override;
	
		void throw_exception( const Axe::Exception & _ex ) override;
	
	protected:
		TBindResponse m_response;
		TBindException m_exception;
	};
	//////////////////////////////////////////////////////////////////////////
	class Response_EvictorManager_get
		: public Axe::Response
	{
	protected:
		virtual void response( const AxeUtil::Archive &, std::size_t _typeId ) = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
		void exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_EvictorManager_get> Response_EvictorManager_getPtr;
	
	template<>
	class BindResponse<Response_EvictorManager_getPtr>
		: public Response_EvictorManager_get
	{
		typedef boost::function<void(const AxeUtil::Archive &, std::size_t)> TBindResponse;
		typedef boost::function<void(const Axe::Exception &)> TBindException;
	
	public:
		BindResponse( const TBindResponse & _response, const TBindException & _exception );
	
	public:
		void response( const AxeUtil::Archive & _arg0, std::size_t _arg1 ) override;
	
		void throw_exception( const Axe::Exception & _ex ) override;
	
	protected:
		TBindResponse m_response;
		TBindException m_exception;
	};
	
	class Proxy_EvictorManager
		: virtual public Axe::Proxy
	{
	public:
		Proxy_EvictorManager( std::size_t _id, const Axe::ConnectionPtr & _connection );
	
	public:
		void set_async( const Response_EvictorManager_setPtr & _response, std::size_t _servantId, std::size_t _typeId, const AxeUtil::Archive & _ar );
		void get_async( const Response_EvictorManager_getPtr & _response, std::size_t _servantId, std::size_t _hostId );
	};
	
	typedef AxeHandle<Proxy_EvictorManager> Proxy_EvictorManagerPtr;
	
	void operator << ( Axe::ArchiveInvocation & _ar, const Proxy_EvictorManagerPtr & _value );
}
