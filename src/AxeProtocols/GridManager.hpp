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
		: virtual public Axe::Exception
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
	
	
	class HostNotFoundException
		: virtual public Axe::Exception
	{
	public:
		void rethrow() const override;
	
	public:
		std::size_t hostId;
	
	public:
		void write( Axe::ArchiveInvocation & _ar ) const override;
		void read( Axe::ArchiveDispatcher & _ar ) override;
	};
	
	typedef AxeHandle<HostNotFoundException> HostNotFoundExceptionPtr;
	
	
	class UniqueAlreadyExistException
		: virtual public Axe::Exception
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
		: virtual public Axe::Exception
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
	
	typedef std::map<std::string, std::size_t> TMapServantTypeIds;
	
	typedef std::map<std::string, Axe::ProxyPtr> TMapUniques;
	
	typedef std::map<std::size_t, std::string> TMapEndpoints;
	
	typedef AxeHandle<class Bellhop_GridManager_addAdapter> Bellhop_GridManager_addAdapterPtr;
	typedef AxeHandle<class Bellhop_GridManager_getAdapterEndpoint> Bellhop_GridManager_getAdapterEndpointPtr;
	typedef AxeHandle<class Bellhop_GridManager_addUnique> Bellhop_GridManager_addUniquePtr;
	typedef AxeHandle<class Bellhop_GridManager_getUnique> Bellhop_GridManager_getUniquePtr;
	typedef AxeHandle<class Bellhop_GridManager_getServantTypeId> Bellhop_GridManager_getServantTypeIdPtr;
	
	class Servant_GridManager
		: virtual public Axe::Servant
	{
	public:
		virtual void addAdapter_async( const Bellhop_GridManager_addAdapterPtr & _cb, const std::string & _name, const std::string & _endpoint ) = 0;
		virtual void getAdapterEndpoint_async( const Bellhop_GridManager_getAdapterEndpointPtr & _cb, std::size_t _hostId ) = 0;
		virtual void addUnique_async( const Bellhop_GridManager_addUniquePtr & _cb, const std::string & _name, const Axe::ProxyPtr & _unique ) = 0;
		virtual void getUnique_async( const Bellhop_GridManager_getUniquePtr & _cb, const std::string & _name ) = 0;
		virtual void getServantTypeId_async( const Bellhop_GridManager_getServantTypeIdPtr & _cb, const std::string & _type ) = 0;
	
	protected:
		TMapAdapterIds m_adapterIds;
		TMapServantTypeIds m_servantTypeIds;
		TMapUniques m_uniques;
		TMapEndpoints m_endpoints;
		std::size_t m_adapterEnumerator;
		std::size_t m_servantTypeEnumerator;
	
	
	private:
		void callMethod( std::size_t _methodId , std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session ) override;
		void responseException( std::size_t _methodId, std::size_t _requestId, const SessionPtr & _session, const Exception & _ex ) override;
	};
	
	typedef AxeHandle<Servant_GridManager> Servant_GridManagerPtr;
	
	void operator << ( Axe::ArchiveInvocation & _ar, const Servant_GridManagerPtr & _value );
	
	
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
	class Bellhop_GridManager_getServantTypeId
		: public Axe::Bellhop
	{
	public:
		Bellhop_GridManager_getServantTypeId( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_GridManagerPtr & _servant );
	
	public:
		void response( std::size_t );
	
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_GridManagerPtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_GridManager_getServantTypeId> Bellhop_GridManager_getServantTypeIdPtr;
	
	//////////////////////////////////////////////////////////////////////////
	class Response_GridManager_addAdapter
		: public Axe::Response
	{
	protected:
		virtual void response( std::size_t ) = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
		void exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_GridManager_addAdapter> Response_GridManager_addAdapterPtr;
	
	template<>
	class BindResponse<Response_GridManager_addAdapterPtr>
		: public Response_GridManager_addAdapter
	{
		typedef boost::function<void(std::size_t)> TBindResponse;
		typedef boost::function<void(const Axe::Exception &)> TBindException;
	
	public:
		BindResponse( const TBindResponse & _response, const TBindException & _exception );
	
	public:
		void response( std::size_t _arg0 ) override;
	
		void throw_exception( const Axe::Exception & _ex ) override;
	
	protected:
		TBindResponse m_response;
		TBindException m_exception;
	};
	//////////////////////////////////////////////////////////////////////////
	class Response_GridManager_getAdapterEndpoint
		: public Axe::Response
	{
	protected:
		virtual void response( const std::string & ) = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
		void exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_GridManager_getAdapterEndpoint> Response_GridManager_getAdapterEndpointPtr;
	
	template<>
	class BindResponse<Response_GridManager_getAdapterEndpointPtr>
		: public Response_GridManager_getAdapterEndpoint
	{
		typedef boost::function<void(const std::string &)> TBindResponse;
		typedef boost::function<void(const Axe::Exception &)> TBindException;
	
	public:
		BindResponse( const TBindResponse & _response, const TBindException & _exception );
	
	public:
		void response( const std::string & _arg0 ) override;
	
		void throw_exception( const Axe::Exception & _ex ) override;
	
	protected:
		TBindResponse m_response;
		TBindException m_exception;
	};
	//////////////////////////////////////////////////////////////////////////
	class Response_GridManager_addUnique
		: public Axe::Response
	{
	protected:
		virtual void response() = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
		void exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_GridManager_addUnique> Response_GridManager_addUniquePtr;
	
	template<>
	class BindResponse<Response_GridManager_addUniquePtr>
		: public Response_GridManager_addUnique
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
	class Response_GridManager_getUnique
		: public Axe::Response
	{
	protected:
		virtual void response( const Axe::ProxyPtr & ) = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
		void exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_GridManager_getUnique> Response_GridManager_getUniquePtr;
	
	template<>
	class BindResponse<Response_GridManager_getUniquePtr>
		: public Response_GridManager_getUnique
	{
		typedef boost::function<void(const Axe::ProxyPtr &)> TBindResponse;
		typedef boost::function<void(const Axe::Exception &)> TBindException;
	
	public:
		BindResponse( const TBindResponse & _response, const TBindException & _exception );
	
	public:
		void response( const Axe::ProxyPtr & _arg0 ) override;
	
		void throw_exception( const Axe::Exception & _ex ) override;
	
	protected:
		TBindResponse m_response;
		TBindException m_exception;
	};
	//////////////////////////////////////////////////////////////////////////
	class Response_GridManager_getServantTypeId
		: public Axe::Response
	{
	protected:
		virtual void response( std::size_t ) = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
		void exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_GridManager_getServantTypeId> Response_GridManager_getServantTypeIdPtr;
	
	template<>
	class BindResponse<Response_GridManager_getServantTypeIdPtr>
		: public Response_GridManager_getServantTypeId
	{
		typedef boost::function<void(std::size_t)> TBindResponse;
		typedef boost::function<void(const Axe::Exception &)> TBindException;
	
	public:
		BindResponse( const TBindResponse & _response, const TBindException & _exception );
	
	public:
		void response( std::size_t _arg0 ) override;
	
		void throw_exception( const Axe::Exception & _ex ) override;
	
	protected:
		TBindResponse m_response;
		TBindException m_exception;
	};
	
	class Proxy_GridManager
		: virtual public Axe::Proxy
	{
	public:
		Proxy_GridManager( std::size_t _id, const Axe::ConnectionPtr & _connection );
	
	public:
		void addAdapter_async( const Response_GridManager_addAdapterPtr & _response, const std::string & _name, const std::string & _endpoint );
		void getAdapterEndpoint_async( const Response_GridManager_getAdapterEndpointPtr & _response, std::size_t _hostId );
		void addUnique_async( const Response_GridManager_addUniquePtr & _response, const std::string & _name, const Axe::ProxyPtr & _unique );
		void getUnique_async( const Response_GridManager_getUniquePtr & _response, const std::string & _name );
		void getServantTypeId_async( const Response_GridManager_getServantTypeIdPtr & _response, const std::string & _type );
	};
	
	typedef AxeHandle<Proxy_GridManager> Proxy_GridManagerPtr;
	
	void operator << ( Axe::ArchiveInvocation & _ar, const Proxy_GridManagerPtr & _value );
}
