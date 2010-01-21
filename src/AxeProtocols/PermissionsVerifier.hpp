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
	
	typedef AxeHandle<class Bellhop_PermissionsVerifier_checkPermissions> Bellhop_PermissionsVerifier_checkPermissionsPtr;
	
	class Servant_PermissionsVerifier
		: virtual public Axe::Servant
	{
	public:
		static const std::string & getTypeId();
	
	public:
		virtual void checkPermissions_async( const Bellhop_PermissionsVerifier_checkPermissionsPtr & _cb, const std::string & _login, const std::string & _password ) = 0;
	
	public:
		void callMethod( std::size_t _methodId , std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session ) override;
		void responseException( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const Axe::Exception & _ex ) override;
	public:
		void writeExceptions_( std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
	};
	
	typedef AxeHandle<Servant_PermissionsVerifier> Servant_PermissionsVerifierPtr;
	
	
	class Bellhop_PermissionsVerifier_checkPermissions
		: public Axe::Bellhop
	{
	public:
		Bellhop_PermissionsVerifier_checkPermissions( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_PermissionsVerifierPtr & _servant );
	
	public:
		void response( bool );
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_PermissionsVerifierPtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_PermissionsVerifier_checkPermissions> Bellhop_PermissionsVerifier_checkPermissionsPtr;
	
	//////////////////////////////////////////////////////////////////////////
	class Response_PermissionsVerifier_checkPermissions
		: public Axe::Response
	{
	protected:
		virtual void response( bool ) = 0;
	
	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_PermissionsVerifier_checkPermissions> Response_PermissionsVerifier_checkPermissionsPtr;
	
	class Proxy_PermissionsVerifier
		: virtual public Axe::Proxy
	{
	public:
		Proxy_PermissionsVerifier( std::size_t _id, const Axe::ProxyAdapterProviderPtr & _adapterProvider );
	
	public:
		void checkPermissions_async( const Response_PermissionsVerifier_checkPermissionsPtr & _response, const std::string & _login, const std::string & _password );
	};
	
	typedef AxeHandle<Proxy_PermissionsVerifier> Proxy_PermissionsVerifierPtr;
}
namespace Axe
{
	
	template<>
	class BindResponse<::Axe::Response_PermissionsVerifier_checkPermissionsPtr>
		: public BindResponseHelper<::Axe::Response_PermissionsVerifier_checkPermissions, void(bool)>
	{
	protected:
		typedef BindResponseHelper<::Axe::Response_PermissionsVerifier_checkPermissions, void(bool)> TBaseHelper;
	
	public:
		BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception );
	
	public:
		void response( bool _arg0 ) override;
	};
	
	void operator << ( Axe::ArchiveInvocation & _ar, const ::Axe::Proxy_PermissionsVerifierPtr & _value );
}
