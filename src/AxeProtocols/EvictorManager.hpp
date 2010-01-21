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
	
	class EvictorNotFoundException
		: virtual public Axe::ProtocolCallException
	{
	public:
		void rethrow() const override;
	
	public:
		std::size_t servantId;
	
	public:
		void write( Axe::ArchiveInvocation & _ar ) const override;
		void read( Axe::ArchiveDispatcher & _ar ) override;
	};
	
	typedef AxeHandle<EvictorNotFoundException> EvictorNotFoundExceptionPtr;
	
	
	class EvictorAlreadyRestored
		: virtual public Axe::ProtocolCallException
	{
	public:
		void rethrow() const override;
	
	public:
		std::size_t servantId;
		std::size_t adapterId;
	
	public:
		void write( Axe::ArchiveInvocation & _ar ) const override;
		void read( Axe::ArchiveDispatcher & _ar ) override;
	};
	
	typedef AxeHandle<EvictorAlreadyRestored> EvictorAlreadyRestoredPtr;
	
	
	class EvictorAlreadyStored
		: virtual public Axe::ProtocolCallException
	{
	public:
		void rethrow() const override;
	
	public:
		std::size_t servantId;
	
	public:
		void write( Axe::ArchiveInvocation & _ar ) const override;
		void read( Axe::ArchiveDispatcher & _ar ) override;
	};
	
	typedef AxeHandle<EvictorAlreadyStored> EvictorAlreadyStoredPtr;
	
	
	typedef AxeHandle<class Bellhop_EvictorManager_create> Bellhop_EvictorManager_createPtr;
	typedef AxeHandle<class Bellhop_EvictorManager_erase> Bellhop_EvictorManager_erasePtr;
	typedef AxeHandle<class Bellhop_EvictorManager_set> Bellhop_EvictorManager_setPtr;
	typedef AxeHandle<class Bellhop_EvictorManager_get> Bellhop_EvictorManager_getPtr;
	
	class Servant_EvictorManager
		: virtual public Axe::Servant
	{
	public:
		static const std::string & getTypeId();
	
	public:
		virtual void create_async( const Bellhop_EvictorManager_createPtr & _cb, std::size_t _adapterId, const std::string & _typeId ) = 0;
		virtual void erase_async( const Bellhop_EvictorManager_erasePtr & _cb, std::size_t _servantId ) = 0;
		virtual void set_async( const Bellhop_EvictorManager_setPtr & _cb, std::size_t _servantId, const AxeUtil::Archive & _ar ) = 0;
		virtual void get_async( const Bellhop_EvictorManager_getPtr & _cb, std::size_t _servantId, std::size_t _adapterId ) = 0;
	
	public:
		void callMethod( std::size_t _methodId , std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session ) override;
		void responseException( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const Axe::Exception & _ex ) override;
	public:
		void writeExceptions_( std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
	};
	
	typedef AxeHandle<Servant_EvictorManager> Servant_EvictorManagerPtr;
	
	
	class Bellhop_EvictorManager_create
		: public Axe::Bellhop
	{
	public:
		Bellhop_EvictorManager_create( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_EvictorManagerPtr & _servant );
	
	public:
		void response( std::size_t );
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_EvictorManagerPtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_EvictorManager_create> Bellhop_EvictorManager_createPtr;
	class Bellhop_EvictorManager_erase
		: public Axe::Bellhop
	{
	public:
		Bellhop_EvictorManager_erase( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_EvictorManagerPtr & _servant );
	
	public:
		void response();
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_EvictorManagerPtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_EvictorManager_erase> Bellhop_EvictorManager_erasePtr;
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
		void response( const AxeUtil::Archive &, const std::string & _typeId );
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_EvictorManagerPtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_EvictorManager_get> Bellhop_EvictorManager_getPtr;
	
	//////////////////////////////////////////////////////////////////////////
	class Response_EvictorManager_create
		: public Axe::Response
	{
	protected:
		virtual void response( std::size_t ) = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_EvictorManager_create> Response_EvictorManager_createPtr;
	//////////////////////////////////////////////////////////////////////////
	class Response_EvictorManager_erase
		: public Axe::Response
	{
	protected:
		virtual void response() = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
		void exceptionCall( std::size_t _exceptionId, Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_EvictorManager_erase> Response_EvictorManager_erasePtr;
	//////////////////////////////////////////////////////////////////////////
	class Response_EvictorManager_set
		: public Axe::Response
	{
	protected:
		virtual void response() = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
		void exceptionCall( std::size_t _exceptionId, Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_EvictorManager_set> Response_EvictorManager_setPtr;
	//////////////////////////////////////////////////////////////////////////
	class Response_EvictorManager_get
		: public Axe::Response
	{
	protected:
		virtual void response( const AxeUtil::Archive &, const std::string & _typeId ) = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
		void exceptionCall( std::size_t _exceptionId, Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_EvictorManager_get> Response_EvictorManager_getPtr;
	
	class Proxy_EvictorManager
		: virtual public Axe::Proxy
	{
	public:
		Proxy_EvictorManager( std::size_t _id, const Axe::ProxyAdapterProviderPtr & _adapterProvider );
	
	public:
		void create_async( const Response_EvictorManager_createPtr & _response, std::size_t _adapterId, const std::string & _typeId );
		void erase_async( const Response_EvictorManager_erasePtr & _response, std::size_t _servantId );
		void set_async( const Response_EvictorManager_setPtr & _response, std::size_t _servantId, const AxeUtil::Archive & _ar );
		void get_async( const Response_EvictorManager_getPtr & _response, std::size_t _servantId, std::size_t _adapterId );
	};
	
	typedef AxeHandle<Proxy_EvictorManager> Proxy_EvictorManagerPtr;
}
namespace Axe
{
	
	template<>
	class BindResponse<::Axe::Response_EvictorManager_createPtr>
		: public BindResponseHelper<::Axe::Response_EvictorManager_create, void(std::size_t)>
	{
	protected:
		typedef BindResponseHelper<::Axe::Response_EvictorManager_create, void(std::size_t)> TBaseHelper;
	
	public:
		BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception );
	
	public:
		void response( std::size_t _arg0 ) override;
	};
	
	template<>
	class BindResponse<::Axe::Response_EvictorManager_erasePtr>
		: public BindResponseHelper<::Axe::Response_EvictorManager_erase, void()>
	{
	protected:
		typedef BindResponseHelper<::Axe::Response_EvictorManager_erase, void()> TBaseHelper;
	
	public:
		BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception );
	
	public:
		void response() override;
	};
	
	template<>
	class BindResponse<::Axe::Response_EvictorManager_setPtr>
		: public BindResponseHelper<::Axe::Response_EvictorManager_set, void()>
	{
	protected:
		typedef BindResponseHelper<::Axe::Response_EvictorManager_set, void()> TBaseHelper;
	
	public:
		BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception );
	
	public:
		void response() override;
	};
	
	template<>
	class BindResponse<::Axe::Response_EvictorManager_getPtr>
		: public BindResponseHelper<::Axe::Response_EvictorManager_get, void(const AxeUtil::Archive &, const std::string &)>
	{
	protected:
		typedef BindResponseHelper<::Axe::Response_EvictorManager_get, void(const AxeUtil::Archive &, const std::string &)> TBaseHelper;
	
	public:
		BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception );
	
	public:
		void response( const AxeUtil::Archive & _arg0, const std::string & _arg1 ) override;
	};
	
	void operator << ( Axe::ArchiveInvocation & _ar, const ::Axe::Proxy_EvictorManagerPtr & _value );
}
