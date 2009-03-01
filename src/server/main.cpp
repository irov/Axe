#	pragma once

#	include "../Axe/pch.hpp"
#	include "../Axe/Adapter.hpp"
#	include "../AxeProtocols/Player.hpp"

#	include <stdio.h>

class MyPermissionsVerifier
	: public Axe::Servant_PermissionsVerifier
{
public:
	void add( const std::string & _login, const std::string & _password )
	{
		m_authentication.insert( std::make_pair(_login, _password) );
	}

protected:
	void checkPermissions( const Axe::Bellhop_PermissionsVerifier_checkPermissionsPtr & _cb, const std::string & _login, const std::string & _password ) override
	{
		TMapAuthentication::const_iterator it_found = m_authentication.find( _login );

		bool successful = false;

		if( it_found != m_authentication.end() )
		{
			successful = it_found->second == _password;
		}
	
		_cb->response( successful );
	}

protected:
	typedef std::map<std::string, std::string> TMapAuthentication;
	TMapAuthentication m_authentication;
};

typedef AxeHandle<MyPermissionsVerifier> MyPermissionsVerifierPtr;

class MyPlayer
	: public Axe::Servant_Player
{
public:
	MyPlayer( const std::string & _login )
		: m_login(_login)
	{		
	}

public:
	void test( const Axe::Bellhop_Player_testPtr & _cb, const std::string & name, int id ) override
	{
		int result = 0;

		if( m_login == name )
		{
			result = id;
		}
		
		_cb->response( result );
	}

protected:
	std::string m_login;
};

class MySessionManager
	: public Axe::Servant_SessionManager
{
public:
	MySessionManager( const Axe::AdapterPtr & _adapter )
		: m_adapter(_adapter)
	{

	}

public:
	void create( const Axe::Bellhop_SessionManager_createPtr & _cb, const std::string & _login ) override
	{
		Axe::Servant_PlayerPtr player = new MyPlayer( _login );

		Axe::ProxyPtr base = m_adapter->addServant( player );

		Axe::Proxy_PlayerPtr playerPrx = Axe::uncheckedCast<Axe::Proxy_PlayerPtr>( base );

		_cb->response( playerPrx );
	}

protected:
	Axe::AdapterPtr m_adapter;
};

class AdapterInitialize
	: public Axe::AdapterInitializeResponse
{
public:
	void onInitialize( const Axe::AdapterPtr & _adapter ) override
	{
		MyPermissionsVerifierPtr permissionsVerifier = new MyPermissionsVerifier();
		permissionsVerifier->setServantId(0);

		permissionsVerifier->add( "test", "test" );

		Axe::Servant_SessionManagerPtr sessionManager = new MySessionManager( _adapter );
		permissionsVerifier->setServantId(1);

		_adapter->addUnique( "PermissionsVerifier", permissionsVerifier );
		_adapter->addUnique( "SessionManager", sessionManager );
	}

	void onFailed() override
	{

	}
};

void main()
{
	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"), 12002);

	unsigned short ep_port = ep.port();

	Axe::AdapterPtr adapter = new Axe::Adapter( ep, "Test" );

	boost::asio::ip::tcp::endpoint grid_ep(boost::asio::ip::address::from_string("127.0.0.1"), 12001);

	adapter->initialize( grid_ep, new AdapterInitialize() );

	adapter->run();
}