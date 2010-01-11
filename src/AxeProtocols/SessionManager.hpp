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
	
	typedef AxeHandle<class Bellhop_Session_destroy> Bellhop_Session_destroyPtr;
	
	class Servant_Session
		: virtual public Axe::Servant
	{
	public:
		virtual void destroy_async( const Bellhop_Session_destroyPtr & _cb ) = 0;
	
	public:
		void callMethod( std::size_t _methodId , std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session ) override;
		void responseException( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const Axe::Exception & _ex ) override;
	public:
		void writeExceptions_( std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
	};
	
	typedef AxeHandle<Servant_Session> Servant_SessionPtr;
	
	
	class Bellhop_Session_destroy
		: public Axe::Bellhop
	{
	public:
		Bellhop_Session_destroy( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_SessionPtr & _servant );
	
	public:
		void response();
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_SessionPtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_Session_destroy> Bellhop_Session_destroyPtr;
	
	//////////////////////////////////////////////////////////////////////////
	class Response_Session_destroy
		: public Axe::Response
	{
	protected:
		virtual void response() = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
		void exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_Session_destroy> Response_Session_destroyPtr;
	
	template<>
	class BindResponse<Response_Session_destroyPtr>
		: public Response_Session_destroy
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
	
	class Proxy_Session
		: virtual public Axe::Proxy
	{
	public:
		Proxy_Session( std::size_t _id, const Axe::ProxyHostProviderPtr & _hostProvider );
	
	public:
		void destroy_async( const Response_Session_destroyPtr & _response );
	};
	
	typedef AxeHandle<Proxy_Session> Proxy_SessionPtr;
	
	void operator << ( Axe::ArchiveInvocation & _ar, const Proxy_SessionPtr & _value );
	
	typedef AxeHandle<class Bellhop_SessionManager_create> Bellhop_SessionManager_createPtr;
	
	class Servant_SessionManager
		: virtual public Axe::Servant
	{
	public:
		virtual void create_async( const Bellhop_SessionManager_createPtr & _cb, const std::string & _login ) = 0;
	
	public:
		void callMethod( std::size_t _methodId , std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session ) override;
		void responseException( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const Axe::Exception & _ex ) override;
	public:
		void writeExceptions_( std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
	};
	
	typedef AxeHandle<Servant_SessionManager> Servant_SessionManagerPtr;
	
	
	class Bellhop_SessionManager_create
		: public Axe::Bellhop
	{
	public:
		Bellhop_SessionManager_create( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_SessionManagerPtr & _servant );
	
	public:
		void response( const Proxy_SessionPtr & );
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_SessionManagerPtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_SessionManager_create> Bellhop_SessionManager_createPtr;
	
	//////////////////////////////////////////////////////////////////////////
	class Response_SessionManager_create
		: public Axe::Response
	{
	protected:
		virtual void response( const Proxy_SessionPtr & ) = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
		void exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_SessionManager_create> Response_SessionManager_createPtr;
	
	template<>
	class BindResponse<Response_SessionManager_createPtr>
		: public Response_SessionManager_create
	{
		typedef boost::function<void(const Proxy_SessionPtr &)> TBindResponse;
		typedef boost::function<void(const Axe::Exception &)> TBindException;
	
	public:
		BindResponse( const TBindResponse & _response, const TBindException & _exception );
	
	public:
		void response( const Proxy_SessionPtr & _arg0 ) override;
	
		void throw_exception( const Axe::Exception & _ex ) override;
	
	protected:
		TBindResponse m_response;
		TBindException m_exception;
	};
	
	class Proxy_SessionManager
		: virtual public Axe::Proxy
	{
	public:
		Proxy_SessionManager( std::size_t _id, const Axe::ProxyHostProviderPtr & _hostProvider );
	
	public:
		void create_async( const Response_SessionManager_createPtr & _response, const std::string & _login );
	};
	
	typedef AxeHandle<Proxy_SessionManager> Proxy_SessionManagerPtr;
	
	void operator << ( Axe::ArchiveInvocation & _ar, const Proxy_SessionManagerPtr & _value );
}
