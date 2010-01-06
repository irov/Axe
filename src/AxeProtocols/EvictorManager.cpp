#	include "pch.hpp"

#	include "EvictorManager.hpp"

#	include <Axe/ArchiveInvocation.hpp>
#	include <Axe/ArchiveDispatcher.hpp>

namespace Axe
{
	
	//////////////////////////////////////////////////////////////////////////
	void EvictingNotFoundException::rethrow() const
	{
		throw *this;
	}
	//////////////////////////////////////////////////////////////////////////
	void EvictingNotFoundException::write( Axe::ArchiveInvocation & _ar ) const
	{
		_ar << servantId;
	}
	//////////////////////////////////////////////////////////////////////////
	void EvictingNotFoundException::read( Axe::ArchiveDispatcher & _ar )
	{
		_ar >> servantId;
	}
	//////////////////////////////////////////////////////////////////////////
	void s_Servant_EvictorManager_callMethod_set( Servant_EvictorManager * _servant, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_EvictorManager_setPtr bellhop = new Bellhop_EvictorManager_set( _requestId, _session, _servant );
	
		std::size_t arg0; _archive >> arg0;
		std::size_t arg1; _archive >> arg1;
		AxeUtil::Archive arg2; _archive >> arg2;
	
		_servant->set_async( bellhop, arg0, arg1, arg2 );
	}
	//////////////////////////////////////////////////////////////////////////
	void s_Servant_EvictorManager_callMethod_get( Servant_EvictorManager * _servant, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_EvictorManager_getPtr bellhop = new Bellhop_EvictorManager_get( _requestId, _session, _servant );
	
		std::size_t arg0; _archive >> arg0;
	
		_servant->get_async( bellhop, arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_EvictorManager_callMethod)( Servant_EvictorManager * _servant, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session );
	//////////////////////////////////////////////////////////////////////////
	static TServant_EvictorManager_callMethod s_Servant_EvictorManager_callMethods[] =
	{
		0
		, &s_Servant_EvictorManager_callMethod_set
		, &s_Servant_EvictorManager_callMethod_get
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_EvictorManager::callMethod( std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		(*s_Servant_EvictorManager_callMethods[ _methodId ])( this, _requestId, _archive, _session );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_EvictorManager_writeException_set( Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		Axe::writeExceptionFilter( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_EvictorManager_writeException_get( Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		try
		{
			_ex.rethrow();
		}
		catch( const EvictingNotFoundException & _ex )
		{
			_ar.writeSize( 3 );
			_ex.write( _ar );
		}
		catch( ... )
		{
			Axe::writeExceptionFilter( _ar );
		}
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_EvictorManager_writeException)( Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
	//////////////////////////////////////////////////////////////////////////
	static TServant_EvictorManager_writeException s_Servant_EvictorManager_writeExceptions[] =
	{
		0
		, &s_Servant_EvictorManager_writeException_set
		, &s_Servant_EvictorManager_writeException_get
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_EvictorManager::responseException( std::size_t _methodId, std::size_t _requestId, const SessionPtr & _session, const Exception & _ex )
	{
		Axe::ArchiveInvocation & aw = _session->beginException( _requestId );
	
		(*s_Servant_EvictorManager_writeExceptions[ _methodId ])( aw, _ex );
	
		_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & _ar, const Servant_EvictorManagerPtr & _value )
	{
		_value->writeProxy( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_EvictorManager_set::Bellhop_EvictorManager_set( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_EvictorManagerPtr & _servant )
		: Axe::Bellhop(_requestId, _session)
		, m_servant(_servant)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_EvictorManager_set::response()
	{
		Axe::ArchiveInvocation & ar = m_session->beginResponse( m_requestId );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_EvictorManager_set::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = m_session->beginException( m_requestId );
		s_Servant_EvictorManager_writeException_set( ar, _ex );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_EvictorManager_get::Bellhop_EvictorManager_get( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_EvictorManagerPtr & _servant )
		: Axe::Bellhop(_requestId, _session)
		, m_servant(_servant)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_EvictorManager_get::response( const AxeUtil::Archive & _arg0, std::size_t _arg1 )
	{
		Axe::ArchiveInvocation & ar = m_session->beginResponse( m_requestId );
		ar << _arg0;
		ar << _arg1;
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_EvictorManager_get::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = m_session->beginException( m_requestId );
		s_Servant_EvictorManager_writeException_get( ar, _ex );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<Response_EvictorManager_setPtr>::BindResponse( const TBindResponse & _response, const TBindException & _exception )
		: m_response(_response)
		, m_exception(_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_EvictorManager_setPtr>::response()
	{
		m_response();
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_EvictorManager_setPtr>::throw_exception( const Axe::Exception & _ex )
	{
		m_exception( _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_EvictorManager_set::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		this->response();
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_EvictorManager_set::exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		std::size_t exceptionId;
		_ar.readSize( exceptionId );
	
		if( this->exceptionFilter( exceptionId, _ar ) == true )
		{
			return;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<Response_EvictorManager_getPtr>::BindResponse( const TBindResponse & _response, const TBindException & _exception )
		: m_response(_response)
		, m_exception(_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_EvictorManager_getPtr>::response( const AxeUtil::Archive & _arg0, std::size_t _arg1 )
	{
		m_response( _arg0, _arg1 );
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_EvictorManager_getPtr>::throw_exception( const Axe::Exception & _ex )
	{
		m_exception( _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_EvictorManager_get::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		AxeUtil::Archive arg0; _ar >> arg0;
		std::size_t arg1; _ar >> arg1;
		this->response( arg0, arg1 );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_EvictorManager_get::exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		std::size_t exceptionId;
		_ar.readSize( exceptionId );
	
		if( this->exceptionFilter( exceptionId, _ar ) == true )
		{
			return;
		}
	
		switch( exceptionId )
		{
		case 2:
			{
				EvictingNotFoundException ex;
				ex.read( _ar );
				this->throw_exception( ex ); 
			}
		};
	}
	//////////////////////////////////////////////////////////////////////////
	Proxy_EvictorManager::Proxy_EvictorManager( std::size_t _id, const Axe::ConnectionPtr & _connection )
		: Axe::Proxy(_id, _connection)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_EvictorManager::set_async( const Response_EvictorManager_setPtr & _response, std::size_t _servantId, std::size_t _typeId, const AxeUtil::Archive & _ar )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 1, _response );
		ar << _servantId;
		ar << _typeId;
		ar << _ar;
	
		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_EvictorManager::get_async( const Response_EvictorManager_getPtr & _response, std::size_t _servantId )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 2, _response );
		ar << _servantId;
	
		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & _ar, const Proxy_EvictorManagerPtr & _value )
	{
		_value->write( _ar );
	}
}
