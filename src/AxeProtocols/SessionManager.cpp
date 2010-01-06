#	include "pch.hpp"

#	include "SessionManager.hpp"

#	include <Axe/ArchiveInvocation.hpp>
#	include <Axe/ArchiveDispatcher.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	void s_Servant_Session_callMethod_destroy( Servant_Session * _servant, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_Session_destroyPtr bellhop = new Bellhop_Session_destroy( _requestId, _session, _servant );
	
	
		_servant->destroy_async( bellhop );
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_Session_callMethod)( Servant_Session * _servant, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session );
	//////////////////////////////////////////////////////////////////////////
	static TServant_Session_callMethod s_Servant_Session_callMethods[] =
	{
		0
		, &s_Servant_Session_callMethod_destroy
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_Session::callMethod( std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		(*s_Servant_Session_callMethods[ _methodId ])( this, _requestId, _archive, _session );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_Session_writeException_destroy( Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		Axe::writeExceptionFilter( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_Session_writeException)( Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
	//////////////////////////////////////////////////////////////////////////
	static TServant_Session_writeException s_Servant_Session_writeExceptions[] =
	{
		0
		, &s_Servant_Session_writeException_destroy
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_Session::responseException( std::size_t _methodId, std::size_t _requestId, const SessionPtr & _session, const Exception & _ex )
	{
		Axe::ArchiveInvocation & aw = _session->beginException( _requestId );
	
		(*s_Servant_Session_writeExceptions[ _methodId ])( aw, _ex );
	
		_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & _ar, const Servant_SessionPtr & _value )
	{
		_value->writeProxy( _ar );
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
		Axe::ArchiveInvocation & ar = m_session->beginResponse( m_requestId );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_Session_destroy::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = m_session->beginException( m_requestId );
		s_Servant_Session_writeException_destroy( ar, _ex );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<Response_Session_destroyPtr>::BindResponse( const TBindResponse & _response, const TBindException & _exception )
		: m_response(_response)
		, m_exception(_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_Session_destroyPtr>::response()
	{
		m_response();
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_Session_destroyPtr>::throw_exception( const Axe::Exception & _ex )
	{
		m_exception( _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_Session_destroy::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		this->response();
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_Session_destroy::exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		std::size_t exceptionId;
		_ar.readSize( exceptionId );
	
		if( this->exceptionFilter( exceptionId, _ar ) == true )
		{
			return;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	Proxy_Session::Proxy_Session( std::size_t _id, const Axe::ConnectionPtr & _connection )
		: Axe::Proxy(_id, _connection)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_Session::destroy_async( const Response_Session_destroyPtr & _response )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 1, _response );
	
		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & _ar, const Proxy_SessionPtr & _value )
	{
		_value->write( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	void s_Servant_SessionManager_callMethod_create( Servant_SessionManager * _servant, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_SessionManager_createPtr bellhop = new Bellhop_SessionManager_create( _requestId, _session, _servant );
	
		std::string arg0; _archive >> arg0;
	
		_servant->create_async( bellhop, arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_SessionManager_callMethod)( Servant_SessionManager * _servant, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session );
	//////////////////////////////////////////////////////////////////////////
	static TServant_SessionManager_callMethod s_Servant_SessionManager_callMethods[] =
	{
		0
		, &s_Servant_SessionManager_callMethod_create
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_SessionManager::callMethod( std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		(*s_Servant_SessionManager_callMethods[ _methodId ])( this, _requestId, _archive, _session );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_SessionManager_writeException_create( Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		Axe::writeExceptionFilter( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_SessionManager_writeException)( Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
	//////////////////////////////////////////////////////////////////////////
	static TServant_SessionManager_writeException s_Servant_SessionManager_writeExceptions[] =
	{
		0
		, &s_Servant_SessionManager_writeException_create
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_SessionManager::responseException( std::size_t _methodId, std::size_t _requestId, const SessionPtr & _session, const Exception & _ex )
	{
		Axe::ArchiveInvocation & aw = _session->beginException( _requestId );
	
		(*s_Servant_SessionManager_writeExceptions[ _methodId ])( aw, _ex );
	
		_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & _ar, const Servant_SessionManagerPtr & _value )
	{
		_value->writeProxy( _ar );
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
		Axe::ArchiveInvocation & ar = m_session->beginResponse( m_requestId );
		ar << _arg0;
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_SessionManager_create::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = m_session->beginException( m_requestId );
		s_Servant_SessionManager_writeException_create( ar, _ex );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<Response_SessionManager_createPtr>::BindResponse( const TBindResponse & _response, const TBindException & _exception )
		: m_response(_response)
		, m_exception(_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_SessionManager_createPtr>::response( const Proxy_SessionPtr & _arg0 )
	{
		m_response( _arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_SessionManager_createPtr>::throw_exception( const Axe::Exception & _ex )
	{
		m_exception( _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_SessionManager_create::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		Proxy_SessionPtr arg0 = Axe::makeProxy<Proxy_SessionPtr>( _ar );
		this->response( arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_SessionManager_create::exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		std::size_t exceptionId;
		_ar.readSize( exceptionId );
	
		if( this->exceptionFilter( exceptionId, _ar ) == true )
		{
			return;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	Proxy_SessionManager::Proxy_SessionManager( std::size_t _id, const Axe::ConnectionPtr & _connection )
		: Axe::Proxy(_id, _connection)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_SessionManager::create_async( const Response_SessionManager_createPtr & _response, const std::string & _login )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 1, _response );
		ar << _login;
	
		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & _ar, const Proxy_SessionManagerPtr & _value )
	{
		_value->write( _ar );
	}
}
