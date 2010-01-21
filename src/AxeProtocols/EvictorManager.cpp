#	include "pch.hpp"

#	include "EvictorManager.hpp"

#	include <Axe/ArchiveInvocation.hpp>
#	include <Axe/ArchiveDispatcher.hpp>
#	include <Axe/ProxyAdapterProvider.hpp>

namespace Axe
{
	
	//////////////////////////////////////////////////////////////////////////
	void EvictorNotFoundException::rethrow() const
	{
		throw *this;
	}
	//////////////////////////////////////////////////////////////////////////
	void EvictorNotFoundException::write( Axe::ArchiveInvocation & _ar ) const
	{
		_ar << servantId;
	}
	//////////////////////////////////////////////////////////////////////////
	void EvictorNotFoundException::read( Axe::ArchiveDispatcher & _ar )
	{
		_ar >> servantId;
	}
	
	//////////////////////////////////////////////////////////////////////////
	void EvictorAlreadyRestored::rethrow() const
	{
		throw *this;
	}
	//////////////////////////////////////////////////////////////////////////
	void EvictorAlreadyRestored::write( Axe::ArchiveInvocation & _ar ) const
	{
		_ar << servantId;
		_ar << adapterId;
	}
	//////////////////////////////////////////////////////////////////////////
	void EvictorAlreadyRestored::read( Axe::ArchiveDispatcher & _ar )
	{
		_ar >> servantId;
		_ar >> adapterId;
	}
	
	//////////////////////////////////////////////////////////////////////////
	void EvictorAlreadyStored::rethrow() const
	{
		throw *this;
	}
	//////////////////////////////////////////////////////////////////////////
	void EvictorAlreadyStored::write( Axe::ArchiveInvocation & _ar ) const
	{
		_ar << servantId;
	}
	//////////////////////////////////////////////////////////////////////////
	void EvictorAlreadyStored::read( Axe::ArchiveDispatcher & _ar )
	{
		_ar >> servantId;
	}
	//////////////////////////////////////////////////////////////////////////
	static std::string s_servant_type_Servant_EvictorManager = "::Axe::Servant_EvictorManager";
	//////////////////////////////////////////////////////////////////////////
	const std::string & Servant_EvictorManager::getTypeId()
	{
		return s_servant_type_Servant_EvictorManager;
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_EvictorManager_callMethod_create( Servant_EvictorManager * _servant, std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_EvictorManager_createPtr bellhop = new Bellhop_EvictorManager_create( _requestId, _session, _servant );
	
		std::size_t arg0; _archive >> arg0;
		std::string arg1; _archive >> arg1;
	
		_servant->create_async( bellhop, arg0, arg1 );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_EvictorManager_callMethod_erase( Servant_EvictorManager * _servant, std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_EvictorManager_erasePtr bellhop = new Bellhop_EvictorManager_erase( _requestId, _session, _servant );
	
		std::size_t arg0; _archive >> arg0;
	
		_servant->erase_async( bellhop, arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_EvictorManager_callMethod_set( Servant_EvictorManager * _servant, std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_EvictorManager_setPtr bellhop = new Bellhop_EvictorManager_set( _requestId, _session, _servant );
	
		std::size_t arg0; _archive >> arg0;
		AxeUtil::Archive arg1; _archive >> arg1;
	
		_servant->set_async( bellhop, arg0, arg1 );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_EvictorManager_callMethod_get( Servant_EvictorManager * _servant, std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_EvictorManager_getPtr bellhop = new Bellhop_EvictorManager_get( _requestId, _session, _servant );
	
		std::size_t arg0; _archive >> arg0;
		std::size_t arg1; _archive >> arg1;
	
		_servant->get_async( bellhop, arg0, arg1 );
	}
	static void s_Servant_EvictorManager_dummyMethod( Servant_EvictorManager * _servant, std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		static_cast<Axe::Servant *>( _servant )->callMethod( _methodId, _requestId, _archive, _session );
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_EvictorManager_callMethod)( Servant_EvictorManager * _servant, std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session );
	//////////////////////////////////////////////////////////////////////////
	static TServant_EvictorManager_callMethod s_Servant_EvictorManager_callMethods[] =
	{
		&s_Servant_EvictorManager_dummyMethod
		, &s_Servant_EvictorManager_callMethod_create
		, &s_Servant_EvictorManager_callMethod_erase
		, &s_Servant_EvictorManager_callMethod_set
		, &s_Servant_EvictorManager_callMethod_get
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_EvictorManager::callMethod( std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		(*s_Servant_EvictorManager_callMethods[ _methodId ])( this, _methodId, _requestId, _archive, _session );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_EvictorManager_writeException_create( Servant_EvictorManager * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		Axe::writeExceptionFilter( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_EvictorManager_writeException_erase( Servant_EvictorManager * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		try
		{
			_ex.rethrow();
		}
		catch( const EvictorNotFoundException & _ex )
		{
			_ar.writeSize( 100 );
			_ex.write( _ar );
		}
		catch( ... )
		{
			Axe::writeExceptionFilter( _ar );
		}
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_EvictorManager_writeException_set( Servant_EvictorManager * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		try
		{
			_ex.rethrow();
		}
		catch( const EvictorNotFoundException & _ex )
		{
			_ar.writeSize( 100 );
			_ex.write( _ar );
		}
		catch( const EvictorAlreadyStored & _ex )
		{
			_ar.writeSize( 101 );
			_ex.write( _ar );
		}
		catch( ... )
		{
			Axe::writeExceptionFilter( _ar );
		}
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_EvictorManager_writeException_get( Servant_EvictorManager * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		try
		{
			_ex.rethrow();
		}
		catch( const EvictorNotFoundException & _ex )
		{
			_ar.writeSize( 100 );
			_ex.write( _ar );
		}
		catch( const EvictorAlreadyRestored & _ex )
		{
			_ar.writeSize( 101 );
			_ex.write( _ar );
		}
		catch( ... )
		{
			Axe::writeExceptionFilter( _ar );
		}
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_EvictorManager_writeException)( Servant_EvictorManager * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
	//////////////////////////////////////////////////////////////////////////
	static TServant_EvictorManager_writeException s_Servant_EvictorManager_writeExceptions[] =
	{
		0
		, &s_Servant_EvictorManager_writeException_create
		, &s_Servant_EvictorManager_writeException_erase
		, &s_Servant_EvictorManager_writeException_set
		, &s_Servant_EvictorManager_writeException_get
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_EvictorManager::responseException( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & aw = _session->beginException( _requestId );
	
		this->writeExceptions_( _methodId, aw, _ex );
	
		_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant_EvictorManager::writeExceptions_( std::size_t _methodId, Axe::ArchiveInvocation & _aw, const Axe::Exception & _ex )
	{
		(*s_Servant_EvictorManager_writeExceptions[ _methodId ])( this, _methodId, _aw, _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_EvictorManager_create::Bellhop_EvictorManager_create( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_EvictorManagerPtr & _servant )
		: Axe::Bellhop(_requestId, _session)
		, m_servant(_servant)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_EvictorManager_create::response( std::size_t _arg0 )
	{
		Axe::ArchiveInvocation & ar = this->beginResponse();
		ar << _arg0;
		this->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_EvictorManager_create::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = this->beginException();
		s_Servant_EvictorManager_writeException_create( AxeUtil::nativePtr(m_servant), 3, ar, _ex );
		this->process();
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_EvictorManager_erase::Bellhop_EvictorManager_erase( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_EvictorManagerPtr & _servant )
		: Axe::Bellhop(_requestId, _session)
		, m_servant(_servant)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_EvictorManager_erase::response()
	{
		Axe::ArchiveInvocation & ar = this->beginResponse();
		this->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_EvictorManager_erase::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = this->beginException();
		s_Servant_EvictorManager_writeException_erase( AxeUtil::nativePtr(m_servant), 4, ar, _ex );
		this->process();
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
		Axe::ArchiveInvocation & ar = this->beginResponse();
		this->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_EvictorManager_set::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = this->beginException();
		s_Servant_EvictorManager_writeException_set( AxeUtil::nativePtr(m_servant), 5, ar, _ex );
		this->process();
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_EvictorManager_get::Bellhop_EvictorManager_get( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_EvictorManagerPtr & _servant )
		: Axe::Bellhop(_requestId, _session)
		, m_servant(_servant)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_EvictorManager_get::response( const AxeUtil::Archive & _arg0, const std::string & _arg1 )
	{
		Axe::ArchiveInvocation & ar = this->beginResponse();
		ar << _arg0;
		ar << _arg1;
		this->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_EvictorManager_get::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = this->beginException();
		s_Servant_EvictorManager_writeException_get( AxeUtil::nativePtr(m_servant), 6, ar, _ex );
		this->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_EvictorManager_create::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		std::size_t arg0; _ar >> arg0;
		this->response( arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_EvictorManager_erase::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		this->response();
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_EvictorManager_erase::exceptionCall( std::size_t _exceptionId, Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		switch( _exceptionId )
		{
		case 100:
			{
				EvictorNotFoundException ex;
				ex.read( _ar );
				this->throw_exception( ex ); 
			}
		};
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_EvictorManager_set::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		this->response();
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_EvictorManager_set::exceptionCall( std::size_t _exceptionId, Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		switch( _exceptionId )
		{
		case 100:
			{
				EvictorNotFoundException ex;
				ex.read( _ar );
				this->throw_exception( ex ); 
			}
		case 101:
			{
				EvictorAlreadyStored ex;
				ex.read( _ar );
				this->throw_exception( ex ); 
			}
		};
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_EvictorManager_get::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		AxeUtil::Archive arg0; _ar >> arg0;
		std::string arg1; _ar >> arg1;
		this->response( arg0, arg1 );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_EvictorManager_get::exceptionCall( std::size_t _exceptionId, Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		switch( _exceptionId )
		{
		case 100:
			{
				EvictorNotFoundException ex;
				ex.read( _ar );
				this->throw_exception( ex ); 
			}
		case 101:
			{
				EvictorAlreadyRestored ex;
				ex.read( _ar );
				this->throw_exception( ex ); 
			}
		};
	}
	//////////////////////////////////////////////////////////////////////////
	Proxy_EvictorManager::Proxy_EvictorManager( std::size_t _id, const Axe::ProxyAdapterProviderPtr & _adapterProvider )
		: Axe::Proxy(_id, _adapterProvider)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_EvictorManager::create_async( const Response_EvictorManager_createPtr & _response, std::size_t _adapterId, const std::string & _typeId )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 1, _response );
		ar << _adapterId;
		ar << _typeId;
	
		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_EvictorManager::erase_async( const Response_EvictorManager_erasePtr & _response, std::size_t _servantId )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 2, _response );
		ar << _servantId;
	
		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_EvictorManager::set_async( const Response_EvictorManager_setPtr & _response, std::size_t _servantId, const AxeUtil::Archive & _ar )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 3, _response );
		ar << _servantId;
		ar << _ar;
	
		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_EvictorManager::get_async( const Response_EvictorManager_getPtr & _response, std::size_t _servantId, std::size_t _adapterId )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 4, _response );
		ar << _servantId;
		ar << _adapterId;
	
		this->processMessage();
	}
}
namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	BindResponse<::Axe::Response_EvictorManager_createPtr>::BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception )
		: TBaseHelper(_response,_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<::Axe::Response_EvictorManager_createPtr>::response( std::size_t _arg0 )
	{
		m_response( _arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<::Axe::Response_EvictorManager_erasePtr>::BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception )
		: TBaseHelper(_response,_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<::Axe::Response_EvictorManager_erasePtr>::response()
	{
		m_response();
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<::Axe::Response_EvictorManager_setPtr>::BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception )
		: TBaseHelper(_response,_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<::Axe::Response_EvictorManager_setPtr>::response()
	{
		m_response();
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<::Axe::Response_EvictorManager_getPtr>::BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception )
		: TBaseHelper(_response,_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<::Axe::Response_EvictorManager_getPtr>::response( const AxeUtil::Archive & _arg0, const std::string & _arg1 )
	{
		m_response( _arg0, _arg1 );
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & _ar, const ::Axe::Proxy_EvictorManagerPtr & _value )
	{
		_value->write( _ar );
	}
}
