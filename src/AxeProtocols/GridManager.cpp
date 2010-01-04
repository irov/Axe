#	include "pch.hpp"

#	include "GridManager.hpp"

#	include <Axe/ArchiveInvocation.hpp>
#	include <Axe/ArchiveDispatcher.hpp>

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
	void HostNotFoundException::rethrow() const
	{
		throw *this;
	}
	//////////////////////////////////////////////////////////////////////////
	void HostNotFoundException::write( Axe::ArchiveInvocation & _ar ) const
	{
		_ar << hostId;
	}
	//////////////////////////////////////////////////////////////////////////
	void HostNotFoundException::read( Axe::ArchiveDispatcher & _ar )
	{
		_ar >> hostId;
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
	void s_Servant_GridManager_callMethod_addAdapter( Servant_GridManager * _servant, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_GridManager_addAdapterPtr bellhop = new Bellhop_GridManager_addAdapter( _requestId, _session, _servant );
	
		std::string arg0; _archive >> arg0;
		std::string arg1; _archive >> arg1;
	
		_servant->addAdapter_async( bellhop, arg0, arg1 );
	}
	//////////////////////////////////////////////////////////////////////////
	void s_Servant_GridManager_callMethod_getAdapterEndpoint( Servant_GridManager * _servant, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_GridManager_getAdapterEndpointPtr bellhop = new Bellhop_GridManager_getAdapterEndpoint( _requestId, _session, _servant );
	
		std::size_t arg0; _archive >> arg0;
	
		_servant->getAdapterEndpoint_async( bellhop, arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void s_Servant_GridManager_callMethod_addUnique( Servant_GridManager * _servant, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_GridManager_addUniquePtr bellhop = new Bellhop_GridManager_addUnique( _requestId, _session, _servant );
	
		std::string arg0; _archive >> arg0;
		ProxyPtr arg1 = Axe::makeProxy<ProxyPtr>( _archive );
	
		_servant->addUnique_async( bellhop, arg0, arg1 );
	}
	//////////////////////////////////////////////////////////////////////////
	void s_Servant_GridManager_callMethod_getUnique( Servant_GridManager * _servant, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_GridManager_getUniquePtr bellhop = new Bellhop_GridManager_getUnique( _requestId, _session, _servant );
	
		std::string arg0; _archive >> arg0;
	
		_servant->getUnique_async( bellhop, arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_GridManager_callMethod)( Servant_GridManager * _servant, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session );
	//////////////////////////////////////////////////////////////////////////
	static TServant_GridManager_callMethod s_Servant_GridManager_callMethods[] =
	{
		0
		, &s_Servant_GridManager_callMethod_addAdapter
		, &s_Servant_GridManager_callMethod_getAdapterEndpoint
		, &s_Servant_GridManager_callMethod_addUnique
		, &s_Servant_GridManager_callMethod_getUnique
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_GridManager::callMethod( std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		(*s_Servant_GridManager_callMethods[ _methodId ])( this, _requestId, _archive, _session );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_GridManager_writeException_addAdapter( Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		try
		{
			_ex.rethrow();
		}
		catch( const AdapterAlreadyExistException & _ex )
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
	static void s_Servant_GridManager_writeException_getAdapterEndpoint( Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		try
		{
			_ex.rethrow();
		}
		catch( const HostNotFoundException & _ex )
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
	static void s_Servant_GridManager_writeException_addUnique( Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		try
		{
			_ex.rethrow();
		}
		catch( const UniqueAlreadyExistException & _ex )
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
	static void s_Servant_GridManager_writeException_getUnique( Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		try
		{
			_ex.rethrow();
		}
		catch( const UniqueNotFoundException & _ex )
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
	typedef void (*TServant_GridManager_writeException)( Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
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
	void Servant_GridManager::responseException( std::size_t _methodId, std::size_t _requestId, const SessionPtr & _session, const Exception & _ex )
	{
		Axe::ArchiveInvocation & aw = _session->beginException( _requestId );
	
		(*s_Servant_GridManager_writeExceptions[ _methodId ])( aw, _ex );
	
		_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & _ar, const Servant_GridManagerPtr & _value )
	{
		_value->write( _ar );
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
		Axe::ArchiveInvocation & ar = m_session->beginResponse( m_requestId );
		ar << _arg0;
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_GridManager_addAdapter::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = m_session->beginException( m_requestId );
		s_Servant_GridManager_writeException_addAdapter( ar, _ex );
		m_session->process();
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
		Axe::ArchiveInvocation & ar = m_session->beginResponse( m_requestId );
		ar << _arg0;
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_GridManager_getAdapterEndpoint::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = m_session->beginException( m_requestId );
		s_Servant_GridManager_writeException_getAdapterEndpoint( ar, _ex );
		m_session->process();
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
		Axe::ArchiveInvocation & ar = m_session->beginResponse( m_requestId );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_GridManager_addUnique::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = m_session->beginException( m_requestId );
		s_Servant_GridManager_writeException_addUnique( ar, _ex );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_GridManager_getUnique::Bellhop_GridManager_getUnique( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_GridManagerPtr & _servant )
		: Axe::Bellhop(_requestId, _session)
		, m_servant(_servant)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_GridManager_getUnique::response( const ProxyPtr & _arg0 )
	{
		Axe::ArchiveInvocation & ar = m_session->beginResponse( m_requestId );
		ar << _arg0;
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_GridManager_getUnique::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = m_session->beginException( m_requestId );
		s_Servant_GridManager_writeException_getUnique( ar, _ex );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<Response_GridManager_addAdapterPtr>::BindResponse( const TBindResponse & _response, const TBindException & _exception )
		: m_response(_response)
		, m_exception(_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_GridManager_addAdapterPtr>::response( std::size_t _arg0 )
	{
		m_response( _arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_GridManager_addAdapterPtr>::throw_exception( const Axe::Exception & _ex )
	{
		m_exception( _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_GridManager_addAdapter::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		std::size_t arg0; _ar >> arg0;
		this->response( arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_GridManager_addAdapter::exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
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
				AdapterAlreadyExistException ex;
				ex.read( _ar );
				this->throw_exception( ex ); 
			}
		};
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<Response_GridManager_getAdapterEndpointPtr>::BindResponse( const TBindResponse & _response, const TBindException & _exception )
		: m_response(_response)
		, m_exception(_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_GridManager_getAdapterEndpointPtr>::response( const std::string & _arg0 )
	{
		m_response( _arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_GridManager_getAdapterEndpointPtr>::throw_exception( const Axe::Exception & _ex )
	{
		m_exception( _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_GridManager_getAdapterEndpoint::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		std::string arg0; _ar >> arg0;
		this->response( arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_GridManager_getAdapterEndpoint::exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
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
				HostNotFoundException ex;
				ex.read( _ar );
				this->throw_exception( ex ); 
			}
		};
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<Response_GridManager_addUniquePtr>::BindResponse( const TBindResponse & _response, const TBindException & _exception )
		: m_response(_response)
		, m_exception(_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_GridManager_addUniquePtr>::response()
	{
		m_response();
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_GridManager_addUniquePtr>::throw_exception( const Axe::Exception & _ex )
	{
		m_exception( _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_GridManager_addUnique::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		this->response();
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_GridManager_addUnique::exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
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
				UniqueAlreadyExistException ex;
				ex.read( _ar );
				this->throw_exception( ex ); 
			}
		};
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<Response_GridManager_getUniquePtr>::BindResponse( const TBindResponse & _response, const TBindException & _exception )
		: m_response(_response)
		, m_exception(_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_GridManager_getUniquePtr>::response( const ProxyPtr & _arg0 )
	{
		m_response( _arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_GridManager_getUniquePtr>::throw_exception( const Axe::Exception & _ex )
	{
		m_exception( _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_GridManager_getUnique::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		ProxyPtr arg0 = Axe::makeProxy<ProxyPtr>( _ar );
		this->response( arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_GridManager_getUnique::exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
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
				UniqueNotFoundException ex;
				ex.read( _ar );
				this->throw_exception( ex ); 
			}
		};
	}
	//////////////////////////////////////////////////////////////////////////
	Proxy_GridManager::Proxy_GridManager( std::size_t _id, const Axe::ConnectionPtr & _connection )
		: Axe::Proxy(_id, _connection)
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
	void Proxy_GridManager::getAdapterEndpoint_async( const Response_GridManager_getAdapterEndpointPtr & _response, std::size_t _hostId )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 2, _response );
		ar << _hostId;
	
		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_GridManager::addUnique_async( const Response_GridManager_addUniquePtr & _response, const std::string & _name, const ProxyPtr & _unique )
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
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & _ar, const Proxy_GridManagerPtr & _value )
	{
		_value->write( _ar );
	}
}
