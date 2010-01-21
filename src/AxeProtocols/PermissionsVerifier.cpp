#	include "pch.hpp"

#	include "PermissionsVerifier.hpp"

#	include <Axe/ArchiveInvocation.hpp>
#	include <Axe/ArchiveDispatcher.hpp>
#	include <Axe/ProxyAdapterProvider.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	static std::string s_servant_type_Servant_PermissionsVerifier = "::Axe::Servant_PermissionsVerifier";
	//////////////////////////////////////////////////////////////////////////
	const std::string & Servant_PermissionsVerifier::getTypeId()
	{
		return s_servant_type_Servant_PermissionsVerifier;
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_PermissionsVerifier_callMethod_checkPermissions( Servant_PermissionsVerifier * _servant, std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_PermissionsVerifier_checkPermissionsPtr bellhop = new Bellhop_PermissionsVerifier_checkPermissions( _requestId, _session, _servant );
	
		std::string arg0; _archive >> arg0;
		std::string arg1; _archive >> arg1;
	
		_servant->checkPermissions_async( bellhop, arg0, arg1 );
	}
	static void s_Servant_PermissionsVerifier_dummyMethod( Servant_PermissionsVerifier * _servant, std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		static_cast<Axe::Servant *>( _servant )->callMethod( _methodId, _requestId, _archive, _session );
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_PermissionsVerifier_callMethod)( Servant_PermissionsVerifier * _servant, std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session );
	//////////////////////////////////////////////////////////////////////////
	static TServant_PermissionsVerifier_callMethod s_Servant_PermissionsVerifier_callMethods[] =
	{
		&s_Servant_PermissionsVerifier_dummyMethod
		, &s_Servant_PermissionsVerifier_callMethod_checkPermissions
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_PermissionsVerifier::callMethod( std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		(*s_Servant_PermissionsVerifier_callMethods[ _methodId ])( this, _methodId, _requestId, _archive, _session );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_PermissionsVerifier_writeException_checkPermissions( Servant_PermissionsVerifier * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		Axe::writeExceptionFilter( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_PermissionsVerifier_writeException)( Servant_PermissionsVerifier * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
	//////////////////////////////////////////////////////////////////////////
	static TServant_PermissionsVerifier_writeException s_Servant_PermissionsVerifier_writeExceptions[] =
	{
		0
		, &s_Servant_PermissionsVerifier_writeException_checkPermissions
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_PermissionsVerifier::responseException( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & aw = _session->beginException( _requestId );
	
		this->writeExceptions_( _methodId, aw, _ex );
	
		_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant_PermissionsVerifier::writeExceptions_( std::size_t _methodId, Axe::ArchiveInvocation & _aw, const Axe::Exception & _ex )
	{
		(*s_Servant_PermissionsVerifier_writeExceptions[ _methodId ])( this, _methodId, _aw, _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_PermissionsVerifier_checkPermissions::Bellhop_PermissionsVerifier_checkPermissions( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_PermissionsVerifierPtr & _servant )
		: Axe::Bellhop(_requestId, _session)
		, m_servant(_servant)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_PermissionsVerifier_checkPermissions::response( bool _arg0 )
	{
		Axe::ArchiveInvocation & ar = this->beginResponse();
		ar << _arg0;
		this->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_PermissionsVerifier_checkPermissions::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = this->beginException();
		s_Servant_PermissionsVerifier_writeException_checkPermissions( AxeUtil::nativePtr(m_servant), 3, ar, _ex );
		this->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_PermissionsVerifier_checkPermissions::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		bool arg0; _ar >> arg0;
		this->response( arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	Proxy_PermissionsVerifier::Proxy_PermissionsVerifier( std::size_t _id, const Axe::ProxyAdapterProviderPtr & _adapterProvider )
		: Axe::Proxy(_id, _adapterProvider)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_PermissionsVerifier::checkPermissions_async( const Response_PermissionsVerifier_checkPermissionsPtr & _response, const std::string & _login, const std::string & _password )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 1, _response );
		ar << _login;
		ar << _password;
	
		this->processMessage();
	}
}
namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	BindResponse<::Axe::Response_PermissionsVerifier_checkPermissionsPtr>::BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception )
		: TBaseHelper(_response,_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<::Axe::Response_PermissionsVerifier_checkPermissionsPtr>::response( bool _arg0 )
	{
		m_response( _arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & _ar, const ::Axe::Proxy_PermissionsVerifierPtr & _value )
	{
		_value->write( _ar );
	}
}
