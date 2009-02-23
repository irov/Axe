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
		void callMethod( std::size_t _methodId , std::size_t _requestId , const Axe::SessionPtr & _session, const Axe::ConnectionCachePtr & _connectionCache ) override;
	};
	
	typedef AxeHandle<Servant_Player> Servant_PlayerPtr;
	
	void operator >> ( Axe::ArchiveRead & _ar, Servant_PlayerPtr & _value );
	void operator << ( Axe::ArchiveWrite & _ar, const Servant_PlayerPtr & _value );
	
	
	class Response_Player_test
		: public Axe::Response
	{
	protected:
		virtual void response( int ) = 0;
	
	public:
		void responseCall( Axe::ArchiveRead & _ar, const Axe::ConnectionCachePtr & _connectionCache ) override;
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
	
	void operator << ( Axe::ArchiveWrite & _ar, const Proxy_PlayerPtr & _value );
	
	
	class Servant_Unique
		: virtual public Axe::Servant
	{
	public:
	
	protected:
	
	private:
		void callMethod( std::size_t _methodId , std::size_t _requestId , const Axe::SessionPtr & _session, const Axe::ConnectionCachePtr & _connectionCache ) override;
	};
	
	typedef AxeHandle<Servant_Unique> Servant_UniquePtr;
	
	void operator >> ( Axe::ArchiveRead & _ar, Servant_UniquePtr & _value );
	void operator << ( Axe::ArchiveWrite & _ar, const Servant_UniquePtr & _value );
	
	
	
	class Proxy_Unique
		: virtual public Axe::Proxy
	{
	public:
		Proxy_Unique( std::size_t _id, const Axe::ConnectionPtr & _connection );
	
	public:
	};
	
	typedef AxeHandle<Proxy_Unique> Proxy_UniquePtr;
	
	void operator << ( Axe::ArchiveWrite & _ar, const Proxy_UniquePtr & _value );
	
	class Bellhop_PermissionsVerifier_checkPermissions
		: public Axe::Bellhop
	{
	public:
		Bellhop_PermissionsVerifier_checkPermissions( std::size_t _requestId, const Axe::SessionPtr & _session );
	
	public:
		void response( bool );
	};
	
	typedef AxeHandle<Bellhop_PermissionsVerifier_checkPermissions> Bellhop_PermissionsVerifier_checkPermissionsPtr;
	
	class Servant_PermissionsVerifier
		:	public Servant_Unique
	{
	public:
		virtual void checkPermissions( const Bellhop_PermissionsVerifier_checkPermissionsPtr & _cb, const std::string & _login, const std::string & _password ) = 0;
	
	protected:
	
	private:
		void callMethod( std::size_t _methodId , std::size_t _requestId , const Axe::SessionPtr & _session, const Axe::ConnectionCachePtr & _connectionCache ) override;
	};
	
	typedef AxeHandle<Servant_PermissionsVerifier> Servant_PermissionsVerifierPtr;
	
	void operator >> ( Axe::ArchiveRead & _ar, Servant_PermissionsVerifierPtr & _value );
	void operator << ( Axe::ArchiveWrite & _ar, const Servant_PermissionsVerifierPtr & _value );
	
	
	class Response_PermissionsVerifier_checkPermissions
		: public Axe::Response
	{
	protected:
		virtual void response( bool ) = 0;
	
	public:
		void responseCall( Axe::ArchiveRead & _ar, const Axe::ConnectionCachePtr & _connectionCache ) override;
	};
	
	typedef AxeHandle<Response_PermissionsVerifier_checkPermissions> Response_PermissionsVerifier_checkPermissionsPtr;
	
	
	class Proxy_PermissionsVerifier
		:	public Proxy_Unique
	{
	public:
		Proxy_PermissionsVerifier( std::size_t _id, const Axe::ConnectionPtr & _connection );
	
	public:
		void checkPermissions( const std::string & _login, const std::string & _password, const Response_PermissionsVerifier_checkPermissionsPtr & _response );
	};
	
	typedef AxeHandle<Proxy_PermissionsVerifier> Proxy_PermissionsVerifierPtr;
	
	void operator << ( Axe::ArchiveWrite & _ar, const Proxy_PermissionsVerifierPtr & _value );
	
	class Bellhop_SessionManager_create
		: public Axe::Bellhop
	{
	public:
		Bellhop_SessionManager_create( std::size_t _requestId, const Axe::SessionPtr & _session );
	
	public:
		void response( const Proxy_PlayerPtr & );
	};
	
	typedef AxeHandle<Bellhop_SessionManager_create> Bellhop_SessionManager_createPtr;
	
	class Servant_SessionManager
		:	public Servant_Unique
	{
	public:
		virtual void create( const Bellhop_SessionManager_createPtr & _cb, const std::string & _login ) = 0;
	
	protected:
	
	private:
		void callMethod( std::size_t _methodId , std::size_t _requestId , const Axe::SessionPtr & _session, const Axe::ConnectionCachePtr & _connectionCache ) override;
	};
	
	typedef AxeHandle<Servant_SessionManager> Servant_SessionManagerPtr;
	
	void operator >> ( Axe::ArchiveRead & _ar, Servant_SessionManagerPtr & _value );
	void operator << ( Axe::ArchiveWrite & _ar, const Servant_SessionManagerPtr & _value );
	
	
	class Response_SessionManager_create
		: public Axe::Response
	{
	protected:
		virtual void response( const Proxy_PlayerPtr & ) = 0;
	
	public:
		void responseCall( Axe::ArchiveRead & _ar, const Axe::ConnectionCachePtr & _connectionCache ) override;
	};
	
	typedef AxeHandle<Response_SessionManager_create> Response_SessionManager_createPtr;
	
	
	class Proxy_SessionManager
		:	public Proxy_Unique
	{
	public:
		Proxy_SessionManager( std::size_t _id, const Axe::ConnectionPtr & _connection );
	
	public:
		void create( const std::string & _login, const Response_SessionManager_createPtr & _response );
	};
	
	typedef AxeHandle<Proxy_SessionManager> Proxy_SessionManagerPtr;
	
	void operator << ( Axe::ArchiveWrite & _ar, const Proxy_SessionManagerPtr & _value );
	
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
	class Bellhop_GridManager_addUnique
		: public Axe::Bellhop
	{
	public:
		Bellhop_GridManager_addUnique( std::size_t _requestId, const Axe::SessionPtr & _session );
	
	public:
		void response();
	};
	
	typedef AxeHandle<Bellhop_GridManager_addUnique> Bellhop_GridManager_addUniquePtr;
	class Bellhop_GridManager_getUnique
		: public Axe::Bellhop
	{
	public:
		Bellhop_GridManager_getUnique( std::size_t _requestId, const Axe::SessionPtr & _session );
	
	public:
		void response( const Proxy_UniquePtr & );
	};
	
	typedef AxeHandle<Bellhop_GridManager_getUnique> Bellhop_GridManager_getUniquePtr;
	
	class Servant_GridManager
		: virtual public Axe::Servant
	{
	public:
		virtual void addAdapter( const Bellhop_GridManager_addAdapterPtr & _cb, const std::string & _name ) = 0;
		virtual void addUnique( const Bellhop_GridManager_addUniquePtr & _cb, const std::string & _name, const Proxy_UniquePtr & _unique ) = 0;
		virtual void getUnique( const Bellhop_GridManager_getUniquePtr & _cb, const std::string & _name ) = 0;
	
	protected:
		TMapAdapterIds m_adapterIds;
		std::size_t m_enumeratorID;
	
	private:
		void callMethod( std::size_t _methodId , std::size_t _requestId , const Axe::SessionPtr & _session, const Axe::ConnectionCachePtr & _connectionCache ) override;
	};
	
	typedef AxeHandle<Servant_GridManager> Servant_GridManagerPtr;
	
	void operator >> ( Axe::ArchiveRead & _ar, Servant_GridManagerPtr & _value );
	void operator << ( Axe::ArchiveWrite & _ar, const Servant_GridManagerPtr & _value );
	
	
	class Response_GridManager_addAdapter
		: public Axe::Response
	{
	protected:
		virtual void response( std::size_t ) = 0;
	
	public:
		void responseCall( Axe::ArchiveRead & _ar, const Axe::ConnectionCachePtr & _connectionCache ) override;
	};
	
	typedef AxeHandle<Response_GridManager_addAdapter> Response_GridManager_addAdapterPtr;
	
	class Response_GridManager_addUnique
		: public Axe::Response
	{
	protected:
		virtual void response() = 0;
	
	public:
		void responseCall( Axe::ArchiveRead & _ar, const Axe::ConnectionCachePtr & _connectionCache ) override;
	};
	
	typedef AxeHandle<Response_GridManager_addUnique> Response_GridManager_addUniquePtr;
	
	class Response_GridManager_getUnique
		: public Axe::Response
	{
	protected:
		virtual void response( const Proxy_UniquePtr & ) = 0;
	
	public:
		void responseCall( Axe::ArchiveRead & _ar, const Axe::ConnectionCachePtr & _connectionCache ) override;
	};
	
	typedef AxeHandle<Response_GridManager_getUnique> Response_GridManager_getUniquePtr;
	
	
	class Proxy_GridManager
		: virtual public Axe::Proxy
	{
	public:
		Proxy_GridManager( std::size_t _id, const Axe::ConnectionPtr & _connection );
	
	public:
		void addAdapter( const std::string & _name, const Response_GridManager_addAdapterPtr & _response );
		void addUnique( const std::string & _name, const Proxy_UniquePtr & _unique, const Response_GridManager_addUniquePtr & _response );
		void getUnique( const std::string & _name, const Response_GridManager_getUniquePtr & _response );
	};
	
	typedef AxeHandle<Proxy_GridManager> Proxy_GridManagerPtr;
	
	void operator << ( Axe::ArchiveWrite & _ar, const Proxy_GridManagerPtr & _value );
}
