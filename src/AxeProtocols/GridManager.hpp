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
	
	class AdapterAlreadyExistException
		: virtual public Axe::ProtocolCallException
	{
	public:
		void rethrow() const override;
	
	public:
		std::string name;
	
	public:
		void write( Axe::ArchiveInvocation & _ar ) const override;
		void read( Axe::ArchiveDispatcher & _ar ) override;
	};
	
	typedef AxeHandle<AdapterAlreadyExistException> AdapterAlreadyExistExceptionPtr;
	
	
	class AdapterNotFoundException
		: virtual public Axe::ProtocolCallException
	{
	public:
		void rethrow() const override;
	
	public:
		std::size_t adapterId;
	
	public:
		void write( Axe::ArchiveInvocation & _ar ) const override;
		void read( Axe::ArchiveDispatcher & _ar ) override;
	};
	
	typedef AxeHandle<AdapterNotFoundException> AdapterNotFoundExceptionPtr;
	
	
	class UniqueAlreadyExistException
		: virtual public Axe::ProtocolCallException
	{
	public:
		void rethrow() const override;
	
	public:
		std::string name;
	
	public:
		void write( Axe::ArchiveInvocation & _ar ) const override;
		void read( Axe::ArchiveDispatcher & _ar ) override;
	};
	
	typedef AxeHandle<UniqueAlreadyExistException> UniqueAlreadyExistExceptionPtr;
	
	
	class UniqueNotFoundException
		: virtual public Axe::ProtocolCallException
	{
	public:
		void rethrow() const override;
	
	public:
		std::string name;
	
	public:
		void write( Axe::ArchiveInvocation & _ar ) const override;
		void read( Axe::ArchiveDispatcher & _ar ) override;
	};
	
	typedef AxeHandle<UniqueNotFoundException> UniqueNotFoundExceptionPtr;
	
	
	typedef std::map<std::string, std::size_t> TMapAdapterIds;
	
	typedef std::map<std::string, Axe::ProxyPtr> TMapUniques;
	
	typedef std::map<std::size_t, std::string> TMapEndpoints;
	
	typedef AxeHandle<class Bellhop_GridManager_addAdapter> Bellhop_GridManager_addAdapterPtr;
	typedef AxeHandle<class Bellhop_GridManager_getAdapterEndpoint> Bellhop_GridManager_getAdapterEndpointPtr;
	typedef AxeHandle<class Bellhop_GridManager_addUnique> Bellhop_GridManager_addUniquePtr;
	typedef AxeHandle<class Bellhop_GridManager_getUnique> Bellhop_GridManager_getUniquePtr;
	
	class Servant_GridManager
		: virtual public Axe::Servant
	{
	public:
		static const std::string & getTypeId();
	
	public:
		virtual void addAdapter_async( const Bellhop_GridManager_addAdapterPtr & _cb, const std::string & _name, const std::string & _endpoint ) = 0;
		virtual void getAdapterEndpoint_async( const Bellhop_GridManager_getAdapterEndpointPtr & _cb, std::size_t _adapterId ) = 0;
		virtual void addUnique_async( const Bellhop_GridManager_addUniquePtr & _cb, const std::string & _name, const Axe::ProxyPtr & _unique ) = 0;
		virtual void getUnique_async( const Bellhop_GridManager_getUniquePtr & _cb, const std::string & _name ) = 0;
	
	public:
		void callMethod( std::size_t _methodId , std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session ) override;
		void responseException( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const Axe::Exception & _ex ) override;
	public:
		void writeExceptions_( std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
	
	protected:
		void _restore( Axe::ArchiveDispatcher & _ar ) override;
		void _evict( Axe::ArchiveInvocation & _aw ) override;
	
	protected:
		TMapAdapterIds m_adapterIds;
		TMapUniques m_uniques;
		TMapEndpoints m_endpoints;
		std::size_t m_adapterEnumerator;
		std::size_t m_servantTypeEnumerator;
	};
	
	typedef AxeHandle<Servant_GridManager> Servant_GridManagerPtr;
	
	
	class Bellhop_GridManager_addAdapter
		: public Axe::Bellhop
	{
	public:
		Bellhop_GridManager_addAdapter( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_GridManagerPtr & _servant );
	
	public:
		void response( std::size_t );
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_GridManagerPtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_GridManager_addAdapter> Bellhop_GridManager_addAdapterPtr;
	class Bellhop_GridManager_getAdapterEndpoint
		: public Axe::Bellhop
	{
	public:
		Bellhop_GridManager_getAdapterEndpoint( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_GridManagerPtr & _servant );
	
	public:
		void response( const std::string & );
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_GridManagerPtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_GridManager_getAdapterEndpoint> Bellhop_GridManager_getAdapterEndpointPtr;
	class Bellhop_GridManager_addUnique
		: public Axe::Bellhop
	{
	public:
		Bellhop_GridManager_addUnique( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_GridManagerPtr & _servant );
	
	public:
		void response();
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_GridManagerPtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_GridManager_addUnique> Bellhop_GridManager_addUniquePtr;
	class Bellhop_GridManager_getUnique
		: public Axe::Bellhop
	{
	public:
		Bellhop_GridManager_getUnique( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_GridManagerPtr & _servant );
	
	public:
		void response( const Axe::ProxyPtr & );
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_GridManagerPtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_GridManager_getUnique> Bellhop_GridManager_getUniquePtr;
	
	//////////////////////////////////////////////////////////////////////////
	class Response_GridManager_addAdapter
		: public Axe::Response
	{
	protected:
		virtual void response( std::size_t ) = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
		void exceptionCall( std::size_t _exceptionId, Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_GridManager_addAdapter> Response_GridManager_addAdapterPtr;
	//////////////////////////////////////////////////////////////////////////
	class Response_GridManager_getAdapterEndpoint
		: public Axe::Response
	{
	protected:
		virtual void response( const std::string & ) = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
		void exceptionCall( std::size_t _exceptionId, Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_GridManager_getAdapterEndpoint> Response_GridManager_getAdapterEndpointPtr;
	//////////////////////////////////////////////////////////////////////////
	class Response_GridManager_addUnique
		: public Axe::Response
	{
	protected:
		virtual void response() = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
		void exceptionCall( std::size_t _exceptionId, Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_GridManager_addUnique> Response_GridManager_addUniquePtr;
	//////////////////////////////////////////////////////////////////////////
	class Response_GridManager_getUnique
		: public Axe::Response
	{
	protected:
		virtual void response( const Axe::ProxyPtr & ) = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
		void exceptionCall( std::size_t _exceptionId, Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_GridManager_getUnique> Response_GridManager_getUniquePtr;
	
	class Proxy_GridManager
		: virtual public Axe::Proxy
	{
	public:
		Proxy_GridManager( std::size_t _id, const Axe::ProxyAdapterProviderPtr & _adapterProvider );
	
	public:
		void addAdapter_async( const Response_GridManager_addAdapterPtr & _response, const std::string & _name, const std::string & _endpoint );
		void getAdapterEndpoint_async( const Response_GridManager_getAdapterEndpointPtr & _response, std::size_t _adapterId );
		void addUnique_async( const Response_GridManager_addUniquePtr & _response, const std::string & _name, const Axe::ProxyPtr & _unique );
		void getUnique_async( const Response_GridManager_getUniquePtr & _response, const std::string & _name );
	};
	
	typedef AxeHandle<Proxy_GridManager> Proxy_GridManagerPtr;
}
namespace Axe
{
	
	template<>
	class BindResponse<::Axe::Response_GridManager_addAdapterPtr>
		: public BindResponseHelper<::Axe::Response_GridManager_addAdapter, void(std::size_t)>
	{
	protected:
		typedef BindResponseHelper<::Axe::Response_GridManager_addAdapter, void(std::size_t)> TBaseHelper;
	
	public:
		BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception );
	
	public:
		void response( std::size_t _arg0 ) override;
	};
	
	template<>
	class BindResponse<::Axe::Response_GridManager_getAdapterEndpointPtr>
		: public BindResponseHelper<::Axe::Response_GridManager_getAdapterEndpoint, void(const std::string &)>
	{
	protected:
		typedef BindResponseHelper<::Axe::Response_GridManager_getAdapterEndpoint, void(const std::string &)> TBaseHelper;
	
	public:
		BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception );
	
	public:
		void response( const std::string & _arg0 ) override;
	};
	
	template<>
	class BindResponse<::Axe::Response_GridManager_addUniquePtr>
		: public BindResponseHelper<::Axe::Response_GridManager_addUnique, void()>
	{
	protected:
		typedef BindResponseHelper<::Axe::Response_GridManager_addUnique, void()> TBaseHelper;
	
	public:
		BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception );
	
	public:
		void response() override;
	};
	
	template<>
	class BindResponse<::Axe::Response_GridManager_getUniquePtr>
		: public BindResponseHelper<::Axe::Response_GridManager_getUnique, void(const Axe::ProxyPtr &)>
	{
	protected:
		typedef BindResponseHelper<::Axe::Response_GridManager_getUnique, void(const Axe::ProxyPtr &)> TBaseHelper;
	
	public:
		BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception );
	
	public:
		void response( const Axe::ProxyPtr & _arg0 ) override;
	};
	
	void operator << ( Axe::ArchiveInvocation & _ar, const ::Axe::Proxy_GridManagerPtr & _value );
}
