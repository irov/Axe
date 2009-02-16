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
		Bellhop_Player_test( std::size_t _requestId, const Axe::SessionPtr & _session );
	
	public:
		void response( int );
	};
	
	typedef AxeHandle<Bellhop_Player_test> Bellhop_Player_testPtr;
	
	class Servant_Player
		: virtual public Axe::Servant
	{
	public:
		virtual void test( const Bellhop_Player_testPtr & _cb, const std::string & name, int id ) = 0;
	
	protected:
	
	private:
		void callMethod( std::size_t _methodId , std::size_t _requestId , const Axe::SessionPtr & _session, const ConnectionCachePtr & _connectionCache ) override;
	};
	
	typedef AxeHandle<Servant_Player> Servant_PlayerPtr;
	
	class Response_Player_test
		: public Axe::Response
	{
	protected:
		virtual void response( int ) = 0;
	
	public:
		void responseCall( Axe::ArchiveRead & _ar, const ConnectionCachePtr & _connectionCache ) override;
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
	
	typedef AxeHandle<Proxy_Player> Proxy_PlayerPtr;
	
	class Bellhop_SessionManager_login
		: public Axe::Bellhop
	{
	public:
		Bellhop_SessionManager_login( std::size_t _requestId, const Axe::SessionPtr & _session );
	
	public:
		void response( const Proxy_PlayerPtr & );
	};
	
	typedef AxeHandle<Bellhop_SessionManager_login> Bellhop_SessionManager_loginPtr;
	
	class Servant_SessionManager
		: virtual public Axe::Servant
	{
	public:
		virtual void login( const Bellhop_SessionManager_loginPtr & _cb, const std::string & _login, const std::string & _password ) = 0;
	
	protected:
	
	private:
		void callMethod( std::size_t _methodId , std::size_t _requestId , const Axe::SessionPtr & _session, const ConnectionCachePtr & _connectionCache ) override;
	};
	
	typedef AxeHandle<Servant_SessionManager> Servant_SessionManagerPtr;
	
	class Response_SessionManager_login
		: public Axe::Response
	{
	protected:
		virtual void response( const Proxy_PlayerPtr & ) = 0;
	
	public:
		void responseCall( Axe::ArchiveRead & _ar, const ConnectionCachePtr & _connectionCache ) override;
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
	
	typedef AxeHandle<Proxy_SessionManager> Proxy_SessionManagerPtr;
	
	typedef std::map<std::string, std::size_t> TMapAdapterIds;
	
	class Bellhop_GridManager_addAdapter
		: public Axe::Bellhop
	{
	public:
		Bellhop_GridManager_addAdapter( std::size_t _requestId, const Axe::SessionPtr & _session );
	
	public:
		void response( std::size_t );
	};
	
	typedef AxeHandle<Bellhop_GridManager_addAdapter> Bellhop_GridManager_addAdapterPtr;
	class Bellhop_GridManager_getSessionManager
		: public Axe::Bellhop
	{
	public:
		Bellhop_GridManager_getSessionManager( std::size_t _requestId, const Axe::SessionPtr & _session );
	
	public:
		void response( const Proxy_SessionManagerPtr & );
	};
	
	typedef AxeHandle<Bellhop_GridManager_getSessionManager> Bellhop_GridManager_getSessionManagerPtr;
	class Bellhop_GridManager_setSessionManager
		: public Axe::Bellhop
	{
	public:
		Bellhop_GridManager_setSessionManager( std::size_t _requestId, const Axe::SessionPtr & _session );
	
	public:
		void response();
	};
	
	typedef AxeHandle<Bellhop_GridManager_setSessionManager> Bellhop_GridManager_setSessionManagerPtr;
	
	class Servant_GridManager
		: virtual public Axe::Servant
	{
	public:
		virtual void addAdapter( const Bellhop_GridManager_addAdapterPtr & _cb, const std::string & _name ) = 0;
		virtual void getSessionManager( const Bellhop_GridManager_getSessionManagerPtr & _cb ) = 0;
		virtual void setSessionManager( const Bellhop_GridManager_setSessionManagerPtr & _cb, const Proxy_SessionManagerPtr & _sessionManager ) = 0;
	
	protected:
		TMapAdapterIds m_adapterIds;
		std::size_t m_enumeratorID;
	
	private:
		void callMethod( std::size_t _methodId , std::size_t _requestId , const Axe::SessionPtr & _session, const ConnectionCachePtr & _connectionCache ) override;
	};
	
	typedef AxeHandle<Servant_GridManager> Servant_GridManagerPtr;
	
	class Response_GridManager_addAdapter
		: public Axe::Response
	{
	protected:
		virtual void response( std::size_t ) = 0;
	
	public:
		void responseCall( Axe::ArchiveRead & _ar, const ConnectionCachePtr & _connectionCache ) override;
	};
	
	typedef AxeHandle<Response_GridManager_addAdapter> Response_GridManager_addAdapterPtr;
	
	class Response_GridManager_getSessionManager
		: public Axe::Response
	{
	protected:
		virtual void response( const Proxy_SessionManagerPtr & ) = 0;
	
	public:
		void responseCall( Axe::ArchiveRead & _ar, const ConnectionCachePtr & _connectionCache ) override;
	};
	
	typedef AxeHandle<Response_GridManager_getSessionManager> Response_GridManager_getSessionManagerPtr;
	
	class Response_GridManager_setSessionManager
		: public Axe::Response
	{
	protected:
		virtual void response() = 0;
	
	public:
		void responseCall( Axe::ArchiveRead & _ar, const ConnectionCachePtr & _connectionCache ) override;
	};
	
	typedef AxeHandle<Response_GridManager_setSessionManager> Response_GridManager_setSessionManagerPtr;
	
	
	class Proxy_GridManager
		: virtual public Axe::Proxy
	{
	public:
		Proxy_GridManager( std::size_t _id, const Axe::ConnectionPtr & _connection );
	
	public:
		void addAdapter( const std::string & _name, const Response_GridManager_addAdapterPtr & _response );
		void getSessionManager( const Response_GridManager_getSessionManagerPtr & _response );
		void setSessionManager( const Proxy_SessionManagerPtr & _sessionManager, const Response_GridManager_setSessionManagerPtr & _response );
	};
	
	typedef AxeHandle<Proxy_GridManager> Proxy_GridManagerPtr;
}
