#	pragma once

#	include <Axe/Bellhop.hpp>
#	include <Axe/Servant.hpp>
#	include <Axe/Response.hpp>
#	include <Axe/Proxy.hpp>
#	include <Axe/Response.hpp>

namespace Axe
{
	class ArchiveWrite;
	class ArchiveRead;
}

namespace Axe
{
	
	class Bellhop_Player_test
		: public Axe::Bellhop
	{
	public:
		Bellhop_Player_test( std::size_t _requestId, const Axe::AdapterSessionPtr & _session );
	
	public:
		void response( int );
	};
	
	typedef AxeHandle<Bellhop_Player_test> Bellhop_Player_testPtr;
	
	class Servant_Player
		: virtual public Axe::Servant
	{
	public:
		virtual void test( const Bellhop_Player_testPtr & _cb, const std::string & name, int id ) = 0;
	
	private:
		void callMethod( std::size_t _methodId , std::size_t _requestId , const Axe::AdapterSessionPtr & _session, const ConnectionCachePtr & _connectionCache ) override;
	};
	
	typedef AxeHandle<Servant_Player> Servant_PlayerPtr;
	
	class Response_Player_test
		: public Axe::Response
	{
	protected:
		virtual void response( int ) = 0;
	
	public:
		void responseCall( Axe::ArchiveRead & _ar ) override;
	};
	
	typedef AxeHandle<Response_Player_test> Response_Player_testPtr;
	
	
	class Proxy_Player
		: virtual public Axe::Proxy
	{
	public:
		Proxy_Player( std::size_t _id, const Axe::ConnectionPtr & _connection );
	
	public:
		void test( const std::string & name, int id, const Response_Player_testPtr & _response );
	};
	
	void operator << ( Axe::ArchiveWrite & ar, const Proxy_Player & _value );
	void operator >> ( Axe::ArchiveRead & ar, Proxy_Player & _value );
	
	typedef AxeHandle<Proxy_Player> Proxy_PlayerPtr;
	
	class Bellhop_SessionManager_login
		: public Axe::Bellhop
	{
	public:
		Bellhop_SessionManager_login( std::size_t _requestId, const Axe::AdapterSessionPtr & _session );
	
	public:
		void response( const Proxy_PlayerPtr & );
	};
	
	typedef AxeHandle<Bellhop_SessionManager_login> Bellhop_SessionManager_loginPtr;
	
	class Servant_SessionManager
		: virtual public Axe::Servant
	{
	public:
		virtual void login( const Bellhop_SessionManager_loginPtr & _cb, const std::string & _login, const std::string & _password ) = 0;
	
	private:
		void callMethod( std::size_t _methodId , std::size_t _requestId , const Axe::AdapterSessionPtr & _session, const ConnectionCachePtr & _connectionCache ) override;
	};
	
	typedef AxeHandle<Servant_SessionManager> Servant_SessionManagerPtr;
	
	class Response_SessionManager_login
		: public Axe::Response
	{
	protected:
		virtual void response( const Proxy_PlayerPtr & ) = 0;
	
	public:
		void responseCall( Axe::ArchiveRead & _ar ) override;
	};
	
	typedef AxeHandle<Response_SessionManager_login> Response_SessionManager_loginPtr;
	
	
	class Proxy_SessionManager
		: virtual public Axe::Proxy
	{
	public:
		Proxy_SessionManager( std::size_t _id, const Axe::ConnectionPtr & _connection );
	
	public:
		void login( const std::string & _login, const std::string & _password, const Response_SessionManager_loginPtr & _response );
	};
	
	void operator << ( Axe::ArchiveWrite & ar, const Proxy_SessionManager & _value );
	void operator >> ( Axe::ArchiveRead & ar, Proxy_SessionManager & _value );
	
	typedef AxeHandle<Proxy_SessionManager> Proxy_SessionManagerPtr;
}
