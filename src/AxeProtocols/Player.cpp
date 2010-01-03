#	include <Axe/pch.hpp>

#	include "Player.hpp"

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
	void operator << ( Axe::ArchiveInvocation & _ar, const Servant_UniquePtr & _value )
	{
		_value->write( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	Proxy_Unique::Proxy_Unique( std::size_t _id, const Axe::ConnectionPtr & _connection )
		: Axe::Proxy(_id, _connection)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & _ar, const Proxy_UniquePtr & _value )
	{
		_value->write( _ar );
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
		Proxy_UniquePtr arg1 = Axe::makeProxy<Proxy_UniquePtr>( _archive );
	
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
	void Bellhop_GridManager_getUnique::response( const Proxy_UniquePtr & _arg0 )
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
	void BindResponse<Response_GridManager_getUniquePtr>::response( const Proxy_UniquePtr & _arg0 )
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
		Proxy_UniquePtr arg0 = Axe::makeProxy<Proxy_UniquePtr>( _ar );
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
	void Proxy_GridManager::addUnique_async( const Response_GridManager_addUniquePtr & _response, const std::string & _name, const Proxy_UniquePtr & _unique )
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
		, &s_Servant_EvictorManager_callMethod_get
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_EvictorManager::callMethod( std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		(*s_Servant_EvictorManager_callMethods[ _methodId ])( this, _requestId, _archive, _session );
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
		_value->write( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_EvictorManager_get::Bellhop_EvictorManager_get( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_EvictorManagerPtr & _servant )
		: Axe::Bellhop(_requestId, _session)
		, m_servant(_servant)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_EvictorManager_get::response( const AxeUtil::Archive & _arg0 )
	{
		Axe::ArchiveInvocation & ar = m_session->beginResponse( m_requestId );
		ar << _arg0;
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
	BindResponse<Response_EvictorManager_getPtr>::BindResponse( const TBindResponse & _response, const TBindException & _exception )
		: m_response(_response)
		, m_exception(_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_EvictorManager_getPtr>::response( const AxeUtil::Archive & _arg0 )
	{
		m_response( _arg0 );
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
		this->response( arg0 );
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
	void Proxy_EvictorManager::get_async( const Response_EvictorManager_getPtr & _response, std::size_t _servantId )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 1, _response );
		ar << _servantId;
	
		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & _ar, const Proxy_EvictorManagerPtr & _value )
	{
		_value->write( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & ar, const PlayerInfo & _value )
	{
		ar << _value.name;
		ar << _value.id;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator >> ( Axe::ArchiveDispatcher & ar, PlayerInfo & _value )
	{
		ar >> _value.name;
		ar >> _value.id;
	}
	//////////////////////////////////////////////////////////////////////////
	void s_Servant_Player_callMethod_test( Servant_Player * _servant, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_Player_testPtr bellhop = new Bellhop_Player_test( _requestId, _session, _servant );
	
		PlayerInfo arg0; _archive >> arg0;
	
		_servant->test_async( bellhop, arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_Player_callMethod)( Servant_Player * _servant, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session );
	//////////////////////////////////////////////////////////////////////////
	static TServant_Player_callMethod s_Servant_Player_callMethods[] =
	{
		0
		, &s_Servant_Player_callMethod_test
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_Player::callMethod( std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		(*s_Servant_Player_callMethods[ _methodId ])( this, _requestId, _archive, _session );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_Player_writeException_test( Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		Axe::writeExceptionFilter( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_Player_writeException)( Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
	//////////////////////////////////////////////////////////////////////////
	static TServant_Player_writeException s_Servant_Player_writeExceptions[] =
	{
		0
		, &s_Servant_Player_writeException_test
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_Player::responseException( std::size_t _methodId, std::size_t _requestId, const SessionPtr & _session, const Exception & _ex )
	{
		Axe::ArchiveInvocation & aw = _session->beginException( _requestId );
	
		(*s_Servant_Player_writeExceptions[ _methodId ])( aw, _ex );
	
		_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & _ar, const Servant_PlayerPtr & _value )
	{
		_value->write( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_Player_test::Bellhop_Player_test( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_PlayerPtr & _servant )
		: Axe::Bellhop(_requestId, _session)
		, m_servant(_servant)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_Player_test::response( int _arg0 )
	{
		Axe::ArchiveInvocation & ar = m_session->beginResponse( m_requestId );
		ar << _arg0;
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_Player_test::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = m_session->beginException( m_requestId );
		s_Servant_Player_writeException_test( ar, _ex );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<Response_Player_testPtr>::BindResponse( const TBindResponse & _response, const TBindException & _exception )
		: m_response(_response)
		, m_exception(_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_Player_testPtr>::response( int _arg0 )
	{
		m_response( _arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_Player_testPtr>::throw_exception( const Axe::Exception & _ex )
	{
		m_exception( _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_Player_test::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		int arg0; _ar >> arg0;
		this->response( arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_Player_test::exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		std::size_t exceptionId;
		_ar.readSize( exceptionId );
	
		if( this->exceptionFilter( exceptionId, _ar ) == true )
		{
			return;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	Proxy_Player::Proxy_Player( std::size_t _id, const Axe::ConnectionPtr & _connection )
		: Axe::Proxy(_id, _connection)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_Player::test_async( const Response_Player_testPtr & _response, const PlayerInfo & info )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 1, _response );
		ar << info;
	
		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & _ar, const Proxy_PlayerPtr & _value )
	{
		_value->write( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	void s_Servant_PermissionsVerifier_callMethod_checkPermissions( Servant_PermissionsVerifier * _servant, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_PermissionsVerifier_checkPermissionsPtr bellhop = new Bellhop_PermissionsVerifier_checkPermissions( _requestId, _session, _servant );
	
		std::string arg0; _archive >> arg0;
		std::string arg1; _archive >> arg1;
	
		_servant->checkPermissions_async( bellhop, arg0, arg1 );
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_PermissionsVerifier_callMethod)( Servant_PermissionsVerifier * _servant, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session );
	//////////////////////////////////////////////////////////////////////////
	static TServant_PermissionsVerifier_callMethod s_Servant_PermissionsVerifier_callMethods[] =
	{
		0
		, &s_Servant_PermissionsVerifier_callMethod_checkPermissions
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_PermissionsVerifier::callMethod( std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		(*s_Servant_PermissionsVerifier_callMethods[ _methodId ])( this, _requestId, _archive, _session );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_PermissionsVerifier_writeException_checkPermissions( Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		Axe::writeExceptionFilter( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_PermissionsVerifier_writeException)( Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
	//////////////////////////////////////////////////////////////////////////
	static TServant_PermissionsVerifier_writeException s_Servant_PermissionsVerifier_writeExceptions[] =
	{
		0
		, &s_Servant_PermissionsVerifier_writeException_checkPermissions
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_PermissionsVerifier::responseException( std::size_t _methodId, std::size_t _requestId, const SessionPtr & _session, const Exception & _ex )
	{
		Axe::ArchiveInvocation & aw = _session->beginException( _requestId );
	
		(*s_Servant_PermissionsVerifier_writeExceptions[ _methodId ])( aw, _ex );
	
		_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & _ar, const Servant_PermissionsVerifierPtr & _value )
	{
		_value->write( _ar );
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
		Axe::ArchiveInvocation & ar = m_session->beginResponse( m_requestId );
		ar << _arg0;
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_PermissionsVerifier_checkPermissions::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = m_session->beginException( m_requestId );
		s_Servant_PermissionsVerifier_writeException_checkPermissions( ar, _ex );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<Response_PermissionsVerifier_checkPermissionsPtr>::BindResponse( const TBindResponse & _response, const TBindException & _exception )
		: m_response(_response)
		, m_exception(_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_PermissionsVerifier_checkPermissionsPtr>::response( bool _arg0 )
	{
		m_response( _arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_PermissionsVerifier_checkPermissionsPtr>::throw_exception( const Axe::Exception & _ex )
	{
		m_exception( _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_PermissionsVerifier_checkPermissions::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		bool arg0; _ar >> arg0;
		this->response( arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_PermissionsVerifier_checkPermissions::exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		std::size_t exceptionId;
		_ar.readSize( exceptionId );
	
		if( this->exceptionFilter( exceptionId, _ar ) == true )
		{
			return;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	Proxy_PermissionsVerifier::Proxy_PermissionsVerifier( std::size_t _id, const Axe::ConnectionPtr & _connection )
		: Axe::Proxy(_id, _connection)
		, Proxy_Unique(_id, _connection)
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
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & _ar, const Proxy_PermissionsVerifierPtr & _value )
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
		_value->write( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_SessionManager_create::Bellhop_SessionManager_create( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_SessionManagerPtr & _servant )
		: Axe::Bellhop(_requestId, _session)
		, m_servant(_servant)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_SessionManager_create::response( const Proxy_PlayerPtr & _arg0 )
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
	void BindResponse<Response_SessionManager_createPtr>::response( const Proxy_PlayerPtr & _arg0 )
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
		Proxy_PlayerPtr arg0 = Axe::makeProxy<Proxy_PlayerPtr>( _ar );
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
		, Proxy_Unique(_id, _connection)
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
