#	include <Axe/pch.hpp>

#	include "Player.hpp"

#	include <Axe/ArchiveWrite.hpp>
#	include <Axe/ArchiveRead.hpp>

namespace Axe
{
	
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveWrite & ar, const PlayerInfo & _value )
	{
		ar << _value.name;
		ar << _value.id;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator >> ( Axe::ArchiveRead & ar, PlayerInfo & _value )
	{
		ar >> _value.name;
		ar >> _value.id;
	}
	
	enum
	{
		ESMD_Player = 0
		,	ESMD_Player_test
	};
	
	//////////////////////////////////////////////////////////////////////////
	void Servant_Player::callMethod( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session )
	{
		Axe::ArchiveRead & ar = _session->getArchiveRead();
		switch( _methodId )
		{
		case ESMD_Player_test:
			{
				Bellhop_Player_testPtr bellhop = new Bellhop_Player_test( _requestId, _session, this );
	
				PlayerInfo arg0; ar >> arg0;
				this->test( bellhop, arg0 );
			}break;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant_Player::responseException( std::size_t _methodId, std::size_t _requestId, const SessionPtr & _session, const Exception & _ex )
	{
		ArchiveWrite & aw = _session->beginException( _requestId );
		this->write_exception( aw, _methodId, _ex );
		_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant_Player::write_exception( Axe::ArchiveWrite & _ar, std::size_t _methodId, const Axe::Exception & _ex )
	{
		switch( _methodId )
		{
		case ESMD_Player_test:
			{
			}break;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveWrite & _ar, const Servant_PlayerPtr & _value )
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
		Axe::ArchiveWrite & ar = m_session->beginResponse( m_requestId );
		ar << _arg0;
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_Player_test::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveWrite & ar = m_session->beginException( m_requestId );
		m_servant->write_exception( ar, ESMD_Player_test, _ex );
		m_session->process();
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Response_Player_test::responseCall( Axe::ArchiveRead & _ar, std::size_t _size )
	{
		int arg0; _ar >> arg0;
		this->response( arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_Player_test::exceptionCall( Axe::ArchiveRead & _ar, std::size_t _size )
	{
		std::size_t ex_method_id;
		_ar.readSize( ex_method_id );
	
	
	}
	
	//////////////////////////////////////////////////////////////////////////
	Proxy_Player::Proxy_Player( std::size_t _id, const Axe::ConnectionPtr & _connection )
		: Axe::Proxy(_id, _connection)
	{
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Proxy_Player::test( const PlayerInfo & info, const Response_Player_testPtr & _response )
	{
		Axe::ArchiveWrite & ar = this->beginMessage( ESMD_Player_test, _response );
		ar << info;
	
		this->processMessage();
	}
	
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveWrite & _ar, const Proxy_PlayerPtr & _value )
	{
		_value->write( _ar );
	}
	
	enum
	{
		ESMD_Unique = 0
	};
	
	//////////////////////////////////////////////////////////////////////////
	void Servant_Unique::callMethod( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session )
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant_Unique::responseException( std::size_t _methodId, std::size_t _requestId, const SessionPtr & _session, const Exception & _ex )
	{
		ArchiveWrite & aw = _session->beginException( _requestId );
		this->write_exception( aw, _methodId, _ex );
		_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant_Unique::write_exception( Axe::ArchiveWrite & _ar, std::size_t _methodId, const Axe::Exception & _ex )
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveWrite & _ar, const Servant_UniquePtr & _value )
	{
		_value->write( _ar );
	}
	
	
	
	//////////////////////////////////////////////////////////////////////////
	Proxy_Unique::Proxy_Unique( std::size_t _id, const Axe::ConnectionPtr & _connection )
		: Axe::Proxy(_id, _connection)
	{
	}
	
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveWrite & _ar, const Proxy_UniquePtr & _value )
	{
		_value->write( _ar );
	}
	
	enum
	{
		ESMD_PermissionsVerifier = 0
		,	ESMD_PermissionsVerifier_checkPermissions
	};
	
	//////////////////////////////////////////////////////////////////////////
	void Servant_PermissionsVerifier::callMethod( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session )
	{
		Axe::ArchiveRead & ar = _session->getArchiveRead();
		switch( _methodId )
		{
		case ESMD_PermissionsVerifier_checkPermissions:
			{
				Bellhop_PermissionsVerifier_checkPermissionsPtr bellhop = new Bellhop_PermissionsVerifier_checkPermissions( _requestId, _session, this );
	
				std::string arg0; ar >> arg0;
				std::string arg1; ar >> arg1;
				this->checkPermissions( bellhop, arg0, arg1 );
			}break;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant_PermissionsVerifier::responseException( std::size_t _methodId, std::size_t _requestId, const SessionPtr & _session, const Exception & _ex )
	{
		ArchiveWrite & aw = _session->beginException( _requestId );
		this->write_exception( aw, _methodId, _ex );
		_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant_PermissionsVerifier::write_exception( Axe::ArchiveWrite & _ar, std::size_t _methodId, const Axe::Exception & _ex )
	{
		switch( _methodId )
		{
		case ESMD_PermissionsVerifier_checkPermissions:
			{
			}break;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveWrite & _ar, const Servant_PermissionsVerifierPtr & _value )
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
		Axe::ArchiveWrite & ar = m_session->beginResponse( m_requestId );
		ar << _arg0;
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_PermissionsVerifier_checkPermissions::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveWrite & ar = m_session->beginException( m_requestId );
		m_servant->write_exception( ar, ESMD_PermissionsVerifier_checkPermissions, _ex );
		m_session->process();
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Response_PermissionsVerifier_checkPermissions::responseCall( Axe::ArchiveRead & _ar, std::size_t _size )
	{
		bool arg0; _ar >> arg0;
		this->response( arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_PermissionsVerifier_checkPermissions::exceptionCall( Axe::ArchiveRead & _ar, std::size_t _size )
	{
		std::size_t ex_method_id;
		_ar.readSize( ex_method_id );
	
	
	}
	
	//////////////////////////////////////////////////////////////////////////
	Proxy_PermissionsVerifier::Proxy_PermissionsVerifier( std::size_t _id, const Axe::ConnectionPtr & _connection )
		: Axe::Proxy(_id, _connection)
		, Proxy_Unique(_id, _connection)
	{
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Proxy_PermissionsVerifier::checkPermissions( const std::string & _login, const std::string & _password, const Response_PermissionsVerifier_checkPermissionsPtr & _response )
	{
		Axe::ArchiveWrite & ar = this->beginMessage( ESMD_PermissionsVerifier_checkPermissions, _response );
		ar << _login;
		ar << _password;
	
		this->processMessage();
	}
	
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveWrite & _ar, const Proxy_PermissionsVerifierPtr & _value )
	{
		_value->write( _ar );
	}
	
	enum
	{
		ESMD_SessionManager = 0
		,	ESMD_SessionManager_create
	};
	
	//////////////////////////////////////////////////////////////////////////
	void Servant_SessionManager::callMethod( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session )
	{
		Axe::ArchiveRead & ar = _session->getArchiveRead();
		switch( _methodId )
		{
		case ESMD_SessionManager_create:
			{
				Bellhop_SessionManager_createPtr bellhop = new Bellhop_SessionManager_create( _requestId, _session, this );
	
				std::string arg0; ar >> arg0;
				this->create( bellhop, arg0 );
			}break;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant_SessionManager::responseException( std::size_t _methodId, std::size_t _requestId, const SessionPtr & _session, const Exception & _ex )
	{
		ArchiveWrite & aw = _session->beginException( _requestId );
		this->write_exception( aw, _methodId, _ex );
		_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant_SessionManager::write_exception( Axe::ArchiveWrite & _ar, std::size_t _methodId, const Axe::Exception & _ex )
	{
		switch( _methodId )
		{
		case ESMD_SessionManager_create:
			{
			}break;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveWrite & _ar, const Servant_SessionManagerPtr & _value )
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
		Axe::ArchiveWrite & ar = m_session->beginResponse( m_requestId );
		ar << _arg0;
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_SessionManager_create::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveWrite & ar = m_session->beginException( m_requestId );
		m_servant->write_exception( ar, ESMD_SessionManager_create, _ex );
		m_session->process();
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Response_SessionManager_create::responseCall( Axe::ArchiveRead & _ar, std::size_t _size )
	{
		Proxy_PlayerPtr arg0 = Axe::makeProxy<Proxy_PlayerPtr>( _ar );
		this->response( arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_SessionManager_create::exceptionCall( Axe::ArchiveRead & _ar, std::size_t _size )
	{
		std::size_t ex_method_id;
		_ar.readSize( ex_method_id );
	
	
	}
	
	//////////////////////////////////////////////////////////////////////////
	Proxy_SessionManager::Proxy_SessionManager( std::size_t _id, const Axe::ConnectionPtr & _connection )
		: Axe::Proxy(_id, _connection)
		, Proxy_Unique(_id, _connection)
	{
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Proxy_SessionManager::create( const std::string & _login, const Response_SessionManager_createPtr & _response )
	{
		Axe::ArchiveWrite & ar = this->beginMessage( ESMD_SessionManager_create, _response );
		ar << _login;
	
		this->processMessage();
	}
	
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveWrite & _ar, const Proxy_SessionManagerPtr & _value )
	{
		_value->write( _ar );
	}
	
	//////////////////////////////////////////////////////////////////////////
	void AdapterAlreadyExistet::write( Axe::ArchiveWrite & _ar ) const
	{
		_ar << name;
	}
	//////////////////////////////////////////////////////////////////////////
	void AdapterAlreadyExistet::read( Axe::ArchiveRead & _ar )
	{
		_ar >> name;
	}
	
	enum
	{
		ESMD_GridManager = 0
		,	ESMD_GridManager_addAdapter
		,	ESMD_GridManager_getAdapterEndpoint
		,	ESMD_GridManager_addUnique
		,	ESMD_GridManager_getUnique
	};
	
	//////////////////////////////////////////////////////////////////////////
	void Servant_GridManager::callMethod( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session )
	{
		Axe::ArchiveRead & ar = _session->getArchiveRead();
		switch( _methodId )
		{
		case ESMD_GridManager_addAdapter:
			{
				Bellhop_GridManager_addAdapterPtr bellhop = new Bellhop_GridManager_addAdapter( _requestId, _session, this );
	
				std::string arg0; ar >> arg0;
				std::string arg1; ar >> arg1;
				this->addAdapter( bellhop, arg0, arg1 );
			}break;
		case ESMD_GridManager_getAdapterEndpoint:
			{
				Bellhop_GridManager_getAdapterEndpointPtr bellhop = new Bellhop_GridManager_getAdapterEndpoint( _requestId, _session, this );
	
				std::size_t arg0; ar >> arg0;
				this->getAdapterEndpoint( bellhop, arg0 );
			}break;
		case ESMD_GridManager_addUnique:
			{
				Bellhop_GridManager_addUniquePtr bellhop = new Bellhop_GridManager_addUnique( _requestId, _session, this );
	
				std::string arg0; ar >> arg0;
				Proxy_UniquePtr arg1 = Axe::makeProxy<Proxy_UniquePtr>( ar );
				this->addUnique( bellhop, arg0, arg1 );
			}break;
		case ESMD_GridManager_getUnique:
			{
				Bellhop_GridManager_getUniquePtr bellhop = new Bellhop_GridManager_getUnique( _requestId, _session, this );
	
				std::string arg0; ar >> arg0;
				this->getUnique( bellhop, arg0 );
			}break;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant_GridManager::responseException( std::size_t _methodId, std::size_t _requestId, const SessionPtr & _session, const Exception & _ex )
	{
		ArchiveWrite & aw = _session->beginException( _requestId );
		this->write_exception( aw, _methodId, _ex );
		_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant_GridManager::write_exception( Axe::ArchiveWrite & _ar, std::size_t _methodId, const Axe::Exception & _ex )
	{
		switch( _methodId )
		{
		case ESMD_GridManager_addAdapter:
			{
				if( const AdapterAlreadyExistet * method_ex = dynamic_cast<const AdapterAlreadyExistet *>( &_ex ) )
				{
					_ar.writeSize( 2 );
					method_ex->write( _ar );
				}
			}break;
		case ESMD_GridManager_getAdapterEndpoint:
			{
			}break;
		case ESMD_GridManager_addUnique:
			{
			}break;
		case ESMD_GridManager_getUnique:
			{
			}break;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveWrite & _ar, const Servant_GridManagerPtr & _value )
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
		Axe::ArchiveWrite & ar = m_session->beginResponse( m_requestId );
		ar << _arg0;
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_GridManager_addAdapter::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveWrite & ar = m_session->beginException( m_requestId );
		m_servant->write_exception( ar, ESMD_GridManager_addAdapter, _ex );
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
		Axe::ArchiveWrite & ar = m_session->beginResponse( m_requestId );
		ar << _arg0;
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_GridManager_getAdapterEndpoint::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveWrite & ar = m_session->beginException( m_requestId );
		m_servant->write_exception( ar, ESMD_GridManager_getAdapterEndpoint, _ex );
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
		Axe::ArchiveWrite & ar = m_session->beginResponse( m_requestId );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_GridManager_addUnique::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveWrite & ar = m_session->beginException( m_requestId );
		m_servant->write_exception( ar, ESMD_GridManager_addUnique, _ex );
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
		Axe::ArchiveWrite & ar = m_session->beginResponse( m_requestId );
		ar << _arg0;
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_GridManager_getUnique::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveWrite & ar = m_session->beginException( m_requestId );
		m_servant->write_exception( ar, ESMD_GridManager_getUnique, _ex );
		m_session->process();
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Response_GridManager_addAdapter::responseCall( Axe::ArchiveRead & _ar, std::size_t _size )
	{
		std::size_t arg0; _ar >> arg0;
		this->response( arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_GridManager_addAdapter::exceptionCall( Axe::ArchiveRead & _ar, std::size_t _size )
	{
		std::size_t ex_method_id;
		_ar.readSize( ex_method_id );
	
		if( ex_method_id == 2 )
		{
			AdapterAlreadyExistet ex;
			ex.read( _ar );
			this->throw_exception( ex ); 
		}
	
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_GridManager_getAdapterEndpoint::responseCall( Axe::ArchiveRead & _ar, std::size_t _size )
	{
		std::string arg0; _ar >> arg0;
		this->response( arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_GridManager_getAdapterEndpoint::exceptionCall( Axe::ArchiveRead & _ar, std::size_t _size )
	{
		std::size_t ex_method_id;
		_ar.readSize( ex_method_id );
	
	
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_GridManager_addUnique::responseCall( Axe::ArchiveRead & _ar, std::size_t _size )
	{
		this->response();
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_GridManager_addUnique::exceptionCall( Axe::ArchiveRead & _ar, std::size_t _size )
	{
		std::size_t ex_method_id;
		_ar.readSize( ex_method_id );
	
	
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_GridManager_getUnique::responseCall( Axe::ArchiveRead & _ar, std::size_t _size )
	{
		Proxy_UniquePtr arg0 = Axe::makeProxy<Proxy_UniquePtr>( _ar );
		this->response( arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_GridManager_getUnique::exceptionCall( Axe::ArchiveRead & _ar, std::size_t _size )
	{
		std::size_t ex_method_id;
		_ar.readSize( ex_method_id );
	
	
	}
	
	//////////////////////////////////////////////////////////////////////////
	Proxy_GridManager::Proxy_GridManager( std::size_t _id, const Axe::ConnectionPtr & _connection )
		: Axe::Proxy(_id, _connection)
	{
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Proxy_GridManager::addAdapter( const std::string & _name, const std::string & _endpoint, const Response_GridManager_addAdapterPtr & _response )
	{
		Axe::ArchiveWrite & ar = this->beginMessage( ESMD_GridManager_addAdapter, _response );
		ar << _name;
		ar << _endpoint;
	
		this->processMessage();
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Proxy_GridManager::getAdapterEndpoint( std::size_t _hostId, const Response_GridManager_getAdapterEndpointPtr & _response )
	{
		Axe::ArchiveWrite & ar = this->beginMessage( ESMD_GridManager_getAdapterEndpoint, _response );
		ar << _hostId;
	
		this->processMessage();
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Proxy_GridManager::addUnique( const std::string & _name, const Proxy_UniquePtr & _unique, const Response_GridManager_addUniquePtr & _response )
	{
		Axe::ArchiveWrite & ar = this->beginMessage( ESMD_GridManager_addUnique, _response );
		ar << _name;
		ar << _unique;
	
		this->processMessage();
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Proxy_GridManager::getUnique( const std::string & _name, const Response_GridManager_getUniquePtr & _response )
	{
		Axe::ArchiveWrite & ar = this->beginMessage( ESMD_GridManager_getUnique, _response );
		ar << _name;
	
		this->processMessage();
	}
	
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveWrite & _ar, const Proxy_GridManagerPtr & _value )
	{
		_value->write( _ar );
	}
}
