#	include "pch.hpp"

#	include "SessionManager.hpp"

#	include <Axe/ArchiveInvocation.hpp>
#	include <Axe/ArchiveDispatcher.hpp>
#	include <Axe/ProxyAdapterProvider.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	static std::string s_servant_type_Servant_Session = "::Axe::Servant_Session";
	//////////////////////////////////////////////////////////////////////////
	const std::string & Servant_Session::getTypeId()
	{
		return s_servant_type_Servant_Session;
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_Session_callMethod_destroy( Servant_Session * _servant, std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_Session_destroyPtr bellhop = new Bellhop_Session_destroy( _requestId, _session, _servant );
	
	
		_servant->destroy_async( bellhop );
	}
	static void s_Servant_Session_dummyMethod( Servant_Session * _servant, std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		static_cast<Axe::Servant *>( _servant )->callMethod( _methodId, _requestId, _archive, _session );
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_Session_callMethod)( Servant_Session * _servant, std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session );
	//////////////////////////////////////////////////////////////////////////
	static TServant_Session_callMethod s_Servant_Session_callMethods[] =
	{
		&s_Servant_Session_dummyMethod
		, &s_Servant_Session_callMethod_destroy
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_Session::callMethod( std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		(*s_Servant_Session_callMethods[ _methodId ])( this, _methodId, _requestId, _archive, _session );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_Session_writeException_destroy( Servant_Session * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		Axe::writeExceptionFilter( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_Session_writeException)( Servant_Session * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
	//////////////////////////////////////////////////////////////////////////
	static TServant_Session_writeException s_Servant_Session_writeExceptions[] =
	{
		0
		, &s_Servant_Session_writeException_destroy
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_Session::responseException( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & aw = _session->beginException( _requestId );
	
		this->writeExceptions_( _methodId, aw, _ex );
	
		_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant_Session::writeExceptions_( std::size_t _methodId, Axe::ArchiveInvocation & _aw, const Axe::Exception & _ex )
	{
		(*s_Servant_Session_writeExceptions[ _methodId ])( this, _methodId, _aw, _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_Session_destroy::Bellhop_Session_destroy( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_SessionPtr & _servant )
		: Axe::Bellhop(_requestId, _session)
		, m_servant(_servant)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_Session_destroy::response()
	{
		Axe::ArchiveInvocation & ar = this->beginResponse();
		this->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_Session_destroy::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = this->beginException();
		s_Servant_Session_writeException_destroy( AxeUtil::nativePtr(m_servant), 3, ar, _ex );
		this->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_Session_destroy::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		this->response();
	}
	//////////////////////////////////////////////////////////////////////////
	Proxy_Session::Proxy_Session( std::size_t _id, const Axe::ProxyAdapterProviderPtr & _adapterProvider )
		: Axe::Proxy(_id, _adapterProvider)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_Session::destroy_async( const Response_Session_destroyPtr & _response )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 1, _response );
	
		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	static std::string s_servant_type_Servant_SessionManager = "::Axe::Servant_SessionManager";
	//////////////////////////////////////////////////////////////////////////
	const std::string & Servant_SessionManager::getTypeId()
	{
		return s_servant_type_Servant_SessionManager;
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_SessionManager_callMethod_create( Servant_SessionManager * _servant, std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_SessionManager_createPtr bellhop = new Bellhop_SessionManager_create( _requestId, _session, _servant );
	
		std::string arg0; _archive >> arg0;
	
		_servant->create_async( bellhop, arg0 );
	}
	static void s_Servant_SessionManager_dummyMethod( Servant_SessionManager * _servant, std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		static_cast<Axe::Servant *>( _servant )->callMethod( _methodId, _requestId, _archive, _session );
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_SessionManager_callMethod)( Servant_SessionManager * _servant, std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session );
	//////////////////////////////////////////////////////////////////////////
	static TServant_SessionManager_callMethod s_Servant_SessionManager_callMethods[] =
	{
		&s_Servant_SessionManager_dummyMethod
		, &s_Servant_SessionManager_callMethod_create
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_SessionManager::callMethod( std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		(*s_Servant_SessionManager_callMethods[ _methodId ])( this, _methodId, _requestId, _archive, _session );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_SessionManager_writeException_create( Servant_SessionManager * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		Axe::writeExceptionFilter( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_SessionManager_writeException)( Servant_SessionManager * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
	//////////////////////////////////////////////////////////////////////////
	static TServant_SessionManager_writeException s_Servant_SessionManager_writeExceptions[] =
	{
		0
		, &s_Servant_SessionManager_writeException_create
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_SessionManager::responseException( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & aw = _session->beginException( _requestId );
	
		this->writeExceptions_( _methodId, aw, _ex );
	
		_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant_SessionManager::writeExceptions_( std::size_t _methodId, Axe::ArchiveInvocation & _aw, const Axe::Exception & _ex )
	{
		(*s_Servant_SessionManager_writeExceptions[ _methodId ])( this, _methodId, _aw, _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_SessionManager_create::Bellhop_SessionManager_create( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_SessionManagerPtr & _servant )
		: Axe::Bellhop(_requestId, _session)
		, m_servant(_servant)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_SessionManager_create::response( const Proxy_SessionPtr & _arg0 )
	{
		Axe::ArchiveInvocation & ar = this->beginResponse();
		ar << _arg0;
		this->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_SessionManager_create::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = this->beginException();
		s_Servant_SessionManager_writeException_create( AxeUtil::nativePtr(m_servant), 3, ar, _ex );
		this->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_SessionManager_create::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		Proxy_SessionPtr arg0 = Axe::makeProxy<Proxy_SessionPtr>( _ar );
		this->response( arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	Proxy_SessionManager::Proxy_SessionManager( std::size_t _id, const Axe::ProxyAdapterProviderPtr & _adapterProvider )
		: Axe::Proxy(_id, _adapterProvider)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_SessionManager::create_async( const Response_SessionManager_createPtr & _response, const std::string & _login )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 1, _response );
		ar << _login;
	
		this->processMessage();
	}
}
namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	BindResponse<::Axe::Response_Session_destroyPtr>::BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception )
		: TBaseHelper(_response,_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<::Axe::Response_Session_destroyPtr>::response()
	{
		m_response();
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & _ar, const ::Axe::Proxy_SessionPtr & _value )
	{
		_value->write( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<::Axe::Response_SessionManager_createPtr>::BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception )
		: TBaseHelper(_response,_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<::Axe::Response_SessionManager_createPtr>::response( const ::Axe::Proxy_SessionPtr & _arg0 )
	{
		m_response( _arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & _ar, const ::Axe::Proxy_SessionManagerPtr & _value )
	{
		_value->write( _ar );
	}
}
