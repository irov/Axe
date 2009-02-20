#	include <Axe/pch.hpp>

#	include "Player.hpp"

#	include <Axe/ArchiveWrite.hpp>
#	include <Axe/ArchiveRead.hpp>

namespace Axe
{
	
	//////////////////////////////////////////////////////////////////////////
	Bellhop_Player_test::Bellhop_Player_test( std::size_t _requestId, const Axe::SessionPtr & _session )
		: Axe::Bellhop(_requestId, _session)
	{
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_Player_test::response( int _arg0 )
	{
		Axe::ArchiveWrite & ar = m_session->beginResponse();
		ar.writeSize( m_requestId );
		ar << _arg0;
		m_session->process();
	}
	
	enum
	{
		ESMD_Player = 0
		,	ESMD_Player_test
	};
	
	//////////////////////////////////////////////////////////////////////////
	void Servant_Player::callMethod( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const ConnectionCachePtr & _connectionCache )
	{
		Axe::ArchiveRead & ar = _session->getArchiveRead();
		switch( _methodId )
		{
		case ESMD_Player_test:
			{
				Bellhop_Player_testPtr bellhop = new Bellhop_Player_test( _requestId, _session );
	
				std::string arg0; ar >> arg0;
				int arg1; ar >> arg1;
				this->test( bellhop, arg0, arg1 );
			}break;
		}
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Response_Player_test::responseCall( Axe::ArchiveRead & _ar, const ConnectionCachePtr & _connectionCache )
	{
		int arg0; _ar >> arg0;
		this->response( arg0 );
	}
	
	//////////////////////////////////////////////////////////////////////////
	Proxy_Player::Proxy_Player( std::size_t _id, const Axe::ConnectionPtr & _connection )
		: Axe::Proxy(_id, _connection)
	{
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Proxy_Player::test( const std::string & name, int id, const Response_Player_testPtr & _response )
	{
		Axe::ArchiveWrite & ar = this->beginMessage( ESMD_Player_test, _response );
		ar << name;
		ar << id;
	
		this->processMessage();
	}
	
	
	
	enum
	{
		ESMD_Unique = 0
	};
	
	//////////////////////////////////////////////////////////////////////////
	void Servant_Unique::callMethod( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const ConnectionCachePtr & _connectionCache )
	{
	}
	
	
	//////////////////////////////////////////////////////////////////////////
	Proxy_Unique::Proxy_Unique( std::size_t _id, const Axe::ConnectionPtr & _connection )
		: Axe::Proxy(_id, _connection)
	{
	}
	
	
	//////////////////////////////////////////////////////////////////////////
	Bellhop_PermissionsVerifier_checkPermissions::Bellhop_PermissionsVerifier_checkPermissions( std::size_t _requestId, const Axe::SessionPtr & _session )
		: Axe::Bellhop(_requestId, _session)
	{
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_PermissionsVerifier_checkPermissions::response( bool _arg0 )
	{
		Axe::ArchiveWrite & ar = m_session->beginResponse();
		ar.writeSize( m_requestId );
		ar << _arg0;
		m_session->process();
	}
	
	enum
	{
		ESMD_PermissionsVerifier = 0
		,	ESMD_PermissionsVerifier_checkPermissions
	};
	
	//////////////////////////////////////////////////////////////////////////
	void Servant_PermissionsVerifier::callMethod( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const ConnectionCachePtr & _connectionCache )
	{
		Axe::ArchiveRead & ar = _session->getArchiveRead();
		switch( _methodId )
		{
		case ESMD_PermissionsVerifier_checkPermissions:
			{
				Bellhop_PermissionsVerifier_checkPermissionsPtr bellhop = new Bellhop_PermissionsVerifier_checkPermissions( _requestId, _session );
	
				std::string arg0; ar >> arg0;
				std::string arg1; ar >> arg1;
				this->checkPermissions( bellhop, arg0, arg1 );
			}break;
		}
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Response_PermissionsVerifier_checkPermissions::responseCall( Axe::ArchiveRead & _ar, const ConnectionCachePtr & _connectionCache )
	{
		bool arg0; _ar >> arg0;
		this->response( arg0 );
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
	Bellhop_SessionManager_create::Bellhop_SessionManager_create( std::size_t _requestId, const Axe::SessionPtr & _session )
		: Axe::Bellhop(_requestId, _session)
	{
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_SessionManager_create::response( const Proxy_PlayerPtr & _arg0 )
	{
		Axe::ArchiveWrite & ar = m_session->beginResponse();
		ar.writeSize( m_requestId );
		ar << _arg0;
		m_session->process();
	}
	
	enum
	{
		ESMD_SessionManager = 0
		,	ESMD_SessionManager_create
	};
	
	//////////////////////////////////////////////////////////////////////////
	void Servant_SessionManager::callMethod( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const ConnectionCachePtr & _connectionCache )
	{
		Axe::ArchiveRead & ar = _session->getArchiveRead();
		switch( _methodId )
		{
		case ESMD_SessionManager_create:
			{
				Bellhop_SessionManager_createPtr bellhop = new Bellhop_SessionManager_create( _requestId, _session );
	
				std::string arg0; ar >> arg0;
				this->create( bellhop, arg0 );
			}break;
		}
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Response_SessionManager_create::responseCall( Axe::ArchiveRead & _ar, const ConnectionCachePtr & _connectionCache )
	{
		Proxy_PlayerPtr arg0 = makeProxy<Proxy_PlayerPtr>( _ar, _connectionCache );
		this->response( arg0 );
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
	Bellhop_GridManager_addAdapter::Bellhop_GridManager_addAdapter( std::size_t _requestId, const Axe::SessionPtr & _session )
		: Axe::Bellhop(_requestId, _session)
	{
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_GridManager_addAdapter::response( std::size_t _arg0 )
	{
		Axe::ArchiveWrite & ar = m_session->beginResponse();
		ar.writeSize( m_requestId );
		ar << _arg0;
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_GridManager_addUnique::Bellhop_GridManager_addUnique( std::size_t _requestId, const Axe::SessionPtr & _session )
		: Axe::Bellhop(_requestId, _session)
	{
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_GridManager_addUnique::response()
	{
		Axe::ArchiveWrite & ar = m_session->beginResponse();
		ar.writeSize( m_requestId );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_GridManager_getUnique::Bellhop_GridManager_getUnique( std::size_t _requestId, const Axe::SessionPtr & _session )
		: Axe::Bellhop(_requestId, _session)
	{
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_GridManager_getUnique::response( const Proxy_UniquePtr & _arg0 )
	{
		Axe::ArchiveWrite & ar = m_session->beginResponse();
		ar.writeSize( m_requestId );
		ar << _arg0;
		m_session->process();
	}
	
	enum
	{
		ESMD_GridManager = 0
		,	ESMD_GridManager_addAdapter
		,	ESMD_GridManager_addUnique
		,	ESMD_GridManager_getUnique
	};
	
	//////////////////////////////////////////////////////////////////////////
	void Servant_GridManager::callMethod( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const ConnectionCachePtr & _connectionCache )
	{
		Axe::ArchiveRead & ar = _session->getArchiveRead();
		switch( _methodId )
		{
		case ESMD_GridManager_addAdapter:
			{
				Bellhop_GridManager_addAdapterPtr bellhop = new Bellhop_GridManager_addAdapter( _requestId, _session );
	
				std::string arg0; ar >> arg0;
				this->addAdapter( bellhop, arg0 );
			}break;
		case ESMD_GridManager_addUnique:
			{
				Bellhop_GridManager_addUniquePtr bellhop = new Bellhop_GridManager_addUnique( _requestId, _session );
	
				std::string arg0; ar >> arg0;
				Proxy_UniquePtr arg1 = makeProxy<Proxy_UniquePtr>( ar, _connectionCache );
				this->addUnique( bellhop, arg0, arg1 );
			}break;
		case ESMD_GridManager_getUnique:
			{
				Bellhop_GridManager_getUniquePtr bellhop = new Bellhop_GridManager_getUnique( _requestId, _session );
	
				std::string arg0; ar >> arg0;
				this->getUnique( bellhop, arg0 );
			}break;
		}
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Response_GridManager_addAdapter::responseCall( Axe::ArchiveRead & _ar, const ConnectionCachePtr & _connectionCache )
	{
		std::size_t arg0; _ar >> arg0;
		this->response( arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_GridManager_addUnique::responseCall( Axe::ArchiveRead & _ar, const ConnectionCachePtr & _connectionCache )
	{
		this->response();
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_GridManager_getUnique::responseCall( Axe::ArchiveRead & _ar, const ConnectionCachePtr & _connectionCache )
	{
		Proxy_UniquePtr arg0 = makeProxy<Proxy_UniquePtr>( _ar, _connectionCache );
		this->response( arg0 );
	}
	
	//////////////////////////////////////////////////////////////////////////
	Proxy_GridManager::Proxy_GridManager( std::size_t _id, const Axe::ConnectionPtr & _connection )
		: Axe::Proxy(_id, _connection)
	{
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Proxy_GridManager::addAdapter( const std::string & _name, const Response_GridManager_addAdapterPtr & _response )
	{
		Axe::ArchiveWrite & ar = this->beginMessage( ESMD_GridManager_addAdapter, _response );
		ar << _name;
	
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
	
}
