#	include "pch.hpp"

#	include "GridManager.hpp"

#	include <Axe/ArchiveInvocation.hpp>
#	include <Axe/ArchiveDispatcher.hpp>
#	include <Axe/ProxyAdapterProvider.hpp>

namespace Axe
{
	
	//////////////////////////////////////////////////////////////////////////
	void AdapterAlreadyExistException::rethrow() const
	{
		throw *this;
	}
	//////////////////////////////////////////////////////////////////////////
	void AdapterAlreadyExistException::write( Axe::ArchiveInvocation & _ar ) const
	{
		_ar << name;
	}
	//////////////////////////////////////////////////////////////////////////
	void AdapterAlreadyExistException::read( Axe::ArchiveDispatcher & _ar )
	{
		_ar >> name;
	}
	
	//////////////////////////////////////////////////////////////////////////
	void AdapterNotFoundException::rethrow() const
	{
		throw *this;
	}
	//////////////////////////////////////////////////////////////////////////
	void AdapterNotFoundException::write( Axe::ArchiveInvocation & _ar ) const
	{
		_ar << adapterId;
	}
	//////////////////////////////////////////////////////////////////////////
	void AdapterNotFoundException::read( Axe::ArchiveDispatcher & _ar )
	{
		_ar >> adapterId;
	}
	
	//////////////////////////////////////////////////////////////////////////
	void UniqueAlreadyExistException::rethrow() const
	{
		throw *this;
	}
	//////////////////////////////////////////////////////////////////////////
	void UniqueAlreadyExistException::write( Axe::ArchiveInvocation & _ar ) const
	{
		_ar << name;
	}
	//////////////////////////////////////////////////////////////////////////
	void UniqueAlreadyExistException::read( Axe::ArchiveDispatcher & _ar )
	{
		_ar >> name;
	}
	
	//////////////////////////////////////////////////////////////////////////
	void UniqueNotFoundException::rethrow() const
	{
		throw *this;
	}
	//////////////////////////////////////////////////////////////////////////
	void UniqueNotFoundException::write( Axe::ArchiveInvocation & _ar ) const
	{
		_ar << name;
	}
	//////////////////////////////////////////////////////////////////////////
	void UniqueNotFoundException::read( Axe::ArchiveDispatcher & _ar )
	{
		_ar >> name;
	}
	//////////////////////////////////////////////////////////////////////////
	static std::string s_servant_type_Servant_GridManager = "::Axe::Servant_GridManager";
	//////////////////////////////////////////////////////////////////////////
	const std::string & Servant_GridManager::getTypeId()
	{
		return s_servant_type_Servant_GridManager;
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_GridManager_callMethod_addAdapter( Servant_GridManager * _servant, std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_GridManager_addAdapterPtr bellhop = new Bellhop_GridManager_addAdapter( _requestId, _session, _servant );
	
		std::string arg0; _archive >> arg0;
		std::string arg1; _archive >> arg1;
	
		_servant->addAdapter_async( bellhop, arg0, arg1 );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_GridManager_callMethod_getAdapterEndpoint( Servant_GridManager * _servant, std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_GridManager_getAdapterEndpointPtr bellhop = new Bellhop_GridManager_getAdapterEndpoint( _requestId, _session, _servant );
	
		std::size_t arg0; _archive >> arg0;
	
		_servant->getAdapterEndpoint_async( bellhop, arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_GridManager_callMethod_addUnique( Servant_GridManager * _servant, std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_GridManager_addUniquePtr bellhop = new Bellhop_GridManager_addUnique( _requestId, _session, _servant );
	
		std::string arg0; _archive >> arg0;
		Axe::ProxyPtr arg1; _archive >> arg1;
	
		_servant->addUnique_async( bellhop, arg0, arg1 );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_GridManager_callMethod_getUnique( Servant_GridManager * _servant, std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_GridManager_getUniquePtr bellhop = new Bellhop_GridManager_getUnique( _requestId, _session, _servant );
	
		std::string arg0; _archive >> arg0;
	
		_servant->getUnique_async( bellhop, arg0 );
	}
	static void s_Servant_GridManager_dummyMethod( Servant_GridManager * _servant, std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		static_cast<Axe::Servant *>( _servant )->callMethod( _methodId, _requestId, _archive, _session );
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_GridManager_callMethod)( Servant_GridManager * _servant, std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session );
	//////////////////////////////////////////////////////////////////////////
	static TServant_GridManager_callMethod s_Servant_GridManager_callMethods[] =
	{
		&s_Servant_GridManager_dummyMethod
		, &s_Servant_GridManager_callMethod_addAdapter
		, &s_Servant_GridManager_callMethod_getAdapterEndpoint
		, &s_Servant_GridManager_callMethod_addUnique
		, &s_Servant_GridManager_callMethod_getUnique
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_GridManager::callMethod( std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		(*s_Servant_GridManager_callMethods[ _methodId ])( this, _methodId, _requestId, _archive, _session );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_GridManager_writeException_addAdapter( Servant_GridManager * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		try
		{
			_ex.rethrow();
		}
		catch( const AdapterAlreadyExistException & _ex )
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
	static void s_Servant_GridManager_writeException_getAdapterEndpoint( Servant_GridManager * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		try
		{
			_ex.rethrow();
		}
		catch( const AdapterNotFoundException & _ex )
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
	static void s_Servant_GridManager_writeException_addUnique( Servant_GridManager * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		try
		{
			_ex.rethrow();
		}
		catch( const UniqueAlreadyExistException & _ex )
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
	static void s_Servant_GridManager_writeException_getUnique( Servant_GridManager * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		try
		{
			_ex.rethrow();
		}
		catch( const UniqueNotFoundException & _ex )
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
	typedef void (*TServant_GridManager_writeException)( Servant_GridManager * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
	//////////////////////////////////////////////////////////////////////////
	static TServant_GridManager_writeException s_Servant_GridManager_writeExceptions[] =
	{
		0
		, &s_Servant_GridManager_writeException_addAdapter
		, &s_Servant_GridManager_writeException_getAdapterEndpoint
		, &s_Servant_GridManager_writeException_addUnique
		, &s_Servant_GridManager_writeException_getUnique
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_GridManager::responseException( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & aw = _session->beginException( _requestId );
	
		this->writeExceptions_( _methodId, aw, _ex );
	
		_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant_GridManager::writeExceptions_( std::size_t _methodId, Axe::ArchiveInvocation & _aw, const Axe::Exception & _ex )
	{
		(*s_Servant_GridManager_writeExceptions[ _methodId ])( this, _methodId, _aw, _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant_GridManager::_restore( Axe::ArchiveDispatcher & _ar )
	{
		_ar >> m_adapterIds;
		_ar >> m_uniques;
		_ar >> m_endpoints;
		_ar >> m_adapterEnumerator;
		_ar >> m_servantTypeEnumerator;
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant_GridManager::_evict( Axe::ArchiveInvocation & _aw )
	{
		_aw << m_adapterIds;
		_aw << m_uniques;
		_aw << m_endpoints;
		_aw << m_adapterEnumerator;
		_aw << m_servantTypeEnumerator;
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_GridManager_addAdapter::Bellhop_GridManager_addAdapter( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_GridManagerPtr & _servant )
		: Axe::Bellhop(_requestId, _session)
		, m_servant(_servant)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_GridManager_addAdapter::response( std::size_t _arg0 )
	{
		Axe::ArchiveInvocation & ar = this->beginResponse();
		ar << _arg0;
		this->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_GridManager_addAdapter::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = this->beginException();
		s_Servant_GridManager_writeException_addAdapter( AxeUtil::nativePtr(m_servant), 3, ar, _ex );
		this->process();
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_GridManager_getAdapterEndpoint::Bellhop_GridManager_getAdapterEndpoint( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_GridManagerPtr & _servant )
		: Axe::Bellhop(_requestId, _session)
		, m_servant(_servant)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_GridManager_getAdapterEndpoint::response( const std::string & _arg0 )
	{
		Axe::ArchiveInvocation & ar = this->beginResponse();
		ar << _arg0;
		this->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_GridManager_getAdapterEndpoint::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = this->beginException();
		s_Servant_GridManager_writeException_getAdapterEndpoint( AxeUtil::nativePtr(m_servant), 4, ar, _ex );
		this->process();
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_GridManager_addUnique::Bellhop_GridManager_addUnique( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_GridManagerPtr & _servant )
		: Axe::Bellhop(_requestId, _session)
		, m_servant(_servant)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_GridManager_addUnique::response()
	{
		Axe::ArchiveInvocation & ar = this->beginResponse();
		this->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_GridManager_addUnique::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = this->beginException();
		s_Servant_GridManager_writeException_addUnique( AxeUtil::nativePtr(m_servant), 5, ar, _ex );
		this->process();
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_GridManager_getUnique::Bellhop_GridManager_getUnique( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_GridManagerPtr & _servant )
		: Axe::Bellhop(_requestId, _session)
		, m_servant(_servant)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_GridManager_getUnique::response( const Axe::ProxyPtr & _arg0 )
	{
		Axe::ArchiveInvocation & ar = this->beginResponse();
		ar << _arg0;
		this->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_GridManager_getUnique::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = this->beginException();
		s_Servant_GridManager_writeException_getUnique( AxeUtil::nativePtr(m_servant), 6, ar, _ex );
		this->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_GridManager_addAdapter::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		std::size_t arg0; _ar >> arg0;
		this->response( arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_GridManager_addAdapter::exceptionCall( std::size_t _exceptionId, Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		switch( _exceptionId )
		{
		case 100:
			{
				AdapterAlreadyExistException ex;
				ex.read( _ar );
				this->throw_exception( ex ); 
			}
		};
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_GridManager_getAdapterEndpoint::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		std::string arg0; _ar >> arg0;
		this->response( arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_GridManager_getAdapterEndpoint::exceptionCall( std::size_t _exceptionId, Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		switch( _exceptionId )
		{
		case 100:
			{
				AdapterNotFoundException ex;
				ex.read( _ar );
				this->throw_exception( ex ); 
			}
		};
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_GridManager_addUnique::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		this->response();
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_GridManager_addUnique::exceptionCall( std::size_t _exceptionId, Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		switch( _exceptionId )
		{
		case 100:
			{
				UniqueAlreadyExistException ex;
				ex.read( _ar );
				this->throw_exception( ex ); 
			}
		};
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_GridManager_getUnique::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		Axe::ProxyPtr arg0; _ar >> arg0;
		this->response( arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_GridManager_getUnique::exceptionCall( std::size_t _exceptionId, Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		switch( _exceptionId )
		{
		case 100:
			{
				UniqueNotFoundException ex;
				ex.read( _ar );
				this->throw_exception( ex ); 
			}
		};
	}
	//////////////////////////////////////////////////////////////////////////
	Proxy_GridManager::Proxy_GridManager( std::size_t _id, const Axe::ProxyAdapterProviderPtr & _adapterProvider )
		: Axe::Proxy(_id, _adapterProvider)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_GridManager::addAdapter_async( const Response_GridManager_addAdapterPtr & _response, const std::string & _name, const std::string & _endpoint )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 1, _response );
		ar << _name;
		ar << _endpoint;
	
		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_GridManager::getAdapterEndpoint_async( const Response_GridManager_getAdapterEndpointPtr & _response, std::size_t _adapterId )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 2, _response );
		ar << _adapterId;
	
		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_GridManager::addUnique_async( const Response_GridManager_addUniquePtr & _response, const std::string & _name, const Axe::ProxyPtr & _unique )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 3, _response );
		ar << _name;
		ar << _unique;
	
		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_GridManager::getUnique_async( const Response_GridManager_getUniquePtr & _response, const std::string & _name )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 4, _response );
		ar << _name;
	
		this->processMessage();
	}
}
namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	BindResponse<::Axe::Response_GridManager_addAdapterPtr>::BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception )
		: TBaseHelper(_response,_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<::Axe::Response_GridManager_addAdapterPtr>::response( std::size_t _arg0 )
	{
		m_response( _arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<::Axe::Response_GridManager_getAdapterEndpointPtr>::BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception )
		: TBaseHelper(_response,_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<::Axe::Response_GridManager_getAdapterEndpointPtr>::response( const std::string & _arg0 )
	{
		m_response( _arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<::Axe::Response_GridManager_addUniquePtr>::BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception )
		: TBaseHelper(_response,_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<::Axe::Response_GridManager_addUniquePtr>::response()
	{
		m_response();
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<::Axe::Response_GridManager_getUniquePtr>::BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception )
		: TBaseHelper(_response,_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<::Axe::Response_GridManager_getUniquePtr>::response( const Axe::ProxyPtr & _arg0 )
	{
		m_response( _arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & _ar, const ::Axe::Proxy_GridManagerPtr & _value )
	{
		_value->write( _ar );
	}
}
