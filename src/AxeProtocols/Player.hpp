#	pragma once

#	include <Axe/Bellhop.hpp>
#	include <Axe/Servant.hpp>
#	include <Axe/Response.hpp>
#	include <Axe/Proxy.hpp>
#	include <Axe/Response.hpp>
#	include <Axe/Exception.hpp>

namespace Axe
{
	class ArchiveWrite;
	class ArchiveRead;
}

namespace Axe
{
	
	struct PlayerInfo
	{
		std::string name;
		int id;
	};
	
	void operator << ( Axe::ArchiveWrite & ar, const PlayerInfo & _value );
	void operator >> ( Axe::ArchiveRead & ar, PlayerInfo & _value );
	
	typedef AxeHandle<class Bellhop_Player_test> Bellhop_Player_testPtr;
	
	class Servant_Player
		: virtual public Axe::Servant
	{
	public:
		virtual void test( const Bellhop_Player_testPtr & _cb, const PlayerInfo & info ) = 0;
	
	protected:
	
	public:
		void write_exception( Axe::ArchiveWrite & _ar, std::size_t _methodId, const Axe::Exception & _ex );
	
	private:
		void callMethod( std::size_t _methodId , std::size_t _requestId , const Axe::SessionPtr & _session ) override;
		void responseException( std::size_t _methodId, std::size_t _requestId, const SessionPtr & _session, const Exception & _ex ) override;
	};
	
	typedef AxeHandle<Servant_Player> Servant_PlayerPtr;
	
	void operator << ( Axe::ArchiveWrite & _ar, const Servant_PlayerPtr & _value );
	
	
	class Bellhop_Player_test
		: public Axe::Bellhop
	{
	public:
		Bellhop_Player_test( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_PlayerPtr & _servant );
	
	public:
		void response( int );
	
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_PlayerPtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_Player_test> Bellhop_Player_testPtr;
	
	//////////////////////////////////////////////////////////////////////////
	class Response_Player_test
		: public Axe::Response
	{
	protected:
		virtual void response( int ) = 0;
	
	public:
		void responseCall( Axe::ArchiveRead & _ar, std::size_t _size ) override;
		void exceptionCall( Axe::ArchiveRead & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_Player_test> Response_Player_testPtr;
	
	template<>
	class BindResponse<Response_Player_testPtr>
		: public Response_Player_test
	{
		typedef boost::function<void(int)> TBindResponse;
		typedef boost::function<void(const Axe::Exception &)> TBindException;
	
	public:
		BindResponse( const TBindResponse & _response, const TBindException & _exception );
	
	public:
		void response( int _arg0 ) override;
	
		void throw_exception( const Axe::Exception & _ex ) override;
	
	protected:
		TBindResponse m_response;
		TBindException m_exception;
	};
	
	class Proxy_Player
		: virtual public Axe::Proxy
	{
	public:
		Proxy_Player( std::size_t _id, const Axe::ConnectionPtr & _connection );
	
	public:
		void test( const Response_Player_testPtr & _response, const PlayerInfo & info );
	};
	
	typedef AxeHandle<Proxy_Player> Proxy_PlayerPtr;
	
	void operator << ( Axe::ArchiveWrite & _ar, const Proxy_PlayerPtr & _value );
	
	
	class Servant_Unique
		: virtual public Axe::Servant
	{
	public:
	
	protected:
	
	public:
		void write_exception( Axe::ArchiveWrite & _ar, std::size_t _methodId, const Axe::Exception & _ex );
	
	private:
		void callMethod( std::size_t _methodId , std::size_t _requestId , const Axe::SessionPtr & _session ) override;
		void responseException( std::size_t _methodId, std::size_t _requestId, const SessionPtr & _session, const Exception & _ex ) override;
	};
	
	typedef AxeHandle<Servant_Unique> Servant_UniquePtr;
	
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
	
	typedef AxeHandle<class Bellhop_PermissionsVerifier_checkPermissions> Bellhop_PermissionsVerifier_checkPermissionsPtr;
	
	class Servant_PermissionsVerifier
		:	public Servant_Unique
	{
	public:
		virtual void checkPermissions( const Bellhop_PermissionsVerifier_checkPermissionsPtr & _cb, const std::string & _login, const std::string & _password ) = 0;
	
	protected:
	
	public:
		void write_exception( Axe::ArchiveWrite & _ar, std::size_t _methodId, const Axe::Exception & _ex );
	
	private:
		void callMethod( std::size_t _methodId , std::size_t _requestId , const Axe::SessionPtr & _session ) override;
		void responseException( std::size_t _methodId, std::size_t _requestId, const SessionPtr & _session, const Exception & _ex ) override;
	};
	
	typedef AxeHandle<Servant_PermissionsVerifier> Servant_PermissionsVerifierPtr;
	
	void operator << ( Axe::ArchiveWrite & _ar, const Servant_PermissionsVerifierPtr & _value );
	
	
	class Bellhop_PermissionsVerifier_checkPermissions
		: public Axe::Bellhop
	{
	public:
		Bellhop_PermissionsVerifier_checkPermissions( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_PermissionsVerifierPtr & _servant );
	
	public:
		void response( bool );
	
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_PermissionsVerifierPtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_PermissionsVerifier_checkPermissions> Bellhop_PermissionsVerifier_checkPermissionsPtr;
	
	//////////////////////////////////////////////////////////////////////////
	class Response_PermissionsVerifier_checkPermissions
		: public Axe::Response
	{
	protected:
		virtual void response( bool ) = 0;
	
	public:
		void responseCall( Axe::ArchiveRead & _ar, std::size_t _size ) override;
		void exceptionCall( Axe::ArchiveRead & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_PermissionsVerifier_checkPermissions> Response_PermissionsVerifier_checkPermissionsPtr;
	
	template<>
	class BindResponse<Response_PermissionsVerifier_checkPermissionsPtr>
		: public Response_PermissionsVerifier_checkPermissions
	{
		typedef boost::function<void(bool)> TBindResponse;
		typedef boost::function<void(const Axe::Exception &)> TBindException;
	
	public:
		BindResponse( const TBindResponse & _response, const TBindException & _exception );
	
	public:
		void response( bool _arg0 ) override;
	
		void throw_exception( const Axe::Exception & _ex ) override;
	
	protected:
		TBindResponse m_response;
		TBindException m_exception;
	};
	
	class Proxy_PermissionsVerifier
		:	public Proxy_Unique
	{
	public:
		Proxy_PermissionsVerifier( std::size_t _id, const Axe::ConnectionPtr & _connection );
	
	public:
		void checkPermissions( const Response_PermissionsVerifier_checkPermissionsPtr & _response, const std::string & _login, const std::string & _password );
	};
	
	typedef AxeHandle<Proxy_PermissionsVerifier> Proxy_PermissionsVerifierPtr;
	
	void operator << ( Axe::ArchiveWrite & _ar, const Proxy_PermissionsVerifierPtr & _value );
	
	typedef AxeHandle<class Bellhop_SessionManager_create> Bellhop_SessionManager_createPtr;
	
	class Servant_SessionManager
		:	public Servant_Unique
	{
	public:
		virtual void create( const Bellhop_SessionManager_createPtr & _cb, const std::string & _login ) = 0;
	
	protected:
	
	public:
		void write_exception( Axe::ArchiveWrite & _ar, std::size_t _methodId, const Axe::Exception & _ex );
	
	private:
		void callMethod( std::size_t _methodId , std::size_t _requestId , const Axe::SessionPtr & _session ) override;
		void responseException( std::size_t _methodId, std::size_t _requestId, const SessionPtr & _session, const Exception & _ex ) override;
	};
	
	typedef AxeHandle<Servant_SessionManager> Servant_SessionManagerPtr;
	
	void operator << ( Axe::ArchiveWrite & _ar, const Servant_SessionManagerPtr & _value );
	
	
	class Bellhop_SessionManager_create
		: public Axe::Bellhop
	{
	public:
		Bellhop_SessionManager_create( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_SessionManagerPtr & _servant );
	
	public:
		void response( const Proxy_PlayerPtr & );
	
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_SessionManagerPtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_SessionManager_create> Bellhop_SessionManager_createPtr;
	
	//////////////////////////////////////////////////////////////////////////
	class Response_SessionManager_create
		: public Axe::Response
	{
	protected:
		virtual void response( const Proxy_PlayerPtr & ) = 0;
	
	public:
		void responseCall( Axe::ArchiveRead & _ar, std::size_t _size ) override;
		void exceptionCall( Axe::ArchiveRead & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_SessionManager_create> Response_SessionManager_createPtr;
	
	template<>
	class BindResponse<Response_SessionManager_createPtr>
		: public Response_SessionManager_create
	{
		typedef boost::function<void(const Proxy_PlayerPtr &)> TBindResponse;
		typedef boost::function<void(const Axe::Exception &)> TBindException;
	
	public:
		BindResponse( const TBindResponse & _response, const TBindException & _exception );
	
	public:
		void response( const Proxy_PlayerPtr & _arg0 ) override;
	
		void throw_exception( const Axe::Exception & _ex ) override;
	
	protected:
		TBindResponse m_response;
		TBindException m_exception;
	};
	
	class Proxy_SessionManager
		:	public Proxy_Unique
	{
	public:
		Proxy_SessionManager( std::size_t _id, const Axe::ConnectionPtr & _connection );
	
	public:
		void create( const Response_SessionManager_createPtr & _response, const std::string & _login );
	};
	
	typedef AxeHandle<Proxy_SessionManager> Proxy_SessionManagerPtr;
	
	void operator << ( Axe::ArchiveWrite & _ar, const Proxy_SessionManagerPtr & _value );
	
	typedef std::map<std::string, std::size_t> TMapAdapterIds;
	
	class AdapterAlreadyExistet
		: virtual public Axe::Exception
	{
	public:
	public:
		std::string name;
	
	public:
		void write( ArchiveWrite & _ar ) const override;
		void read( Axe::ArchiveRead & _ar ) override;
	};
	
	typedef AxeHandle<AdapterAlreadyExistet> AdapterAlreadyExistetPtr;
	
	
	typedef AxeHandle<class Bellhop_GridManager_addAdapter> Bellhop_GridManager_addAdapterPtr;
	typedef AxeHandle<class Bellhop_GridManager_getAdapterEndpoint> Bellhop_GridManager_getAdapterEndpointPtr;
	typedef AxeHandle<class Bellhop_GridManager_addUnique> Bellhop_GridManager_addUniquePtr;
	typedef AxeHandle<class Bellhop_GridManager_getUnique> Bellhop_GridManager_getUniquePtr;
	
	class Servant_GridManager
		: virtual public Axe::Servant
	{
	public:
		virtual void addAdapter( const Bellhop_GridManager_addAdapterPtr & _cb, const std::string & _name, const std::string & _endpoint ) = 0;
		virtual void getAdapterEndpoint( const Bellhop_GridManager_getAdapterEndpointPtr & _cb, std::size_t _hostId ) = 0;
		virtual void addUnique( const Bellhop_GridManager_addUniquePtr & _cb, const std::string & _name, const Proxy_UniquePtr & _unique ) = 0;
		virtual void getUnique( const Bellhop_GridManager_getUniquePtr & _cb, const std::string & _name ) = 0;
	
	protected:
		TMapAdapterIds m_adapterIds;
		std::size_t m_enumeratorID;
	
	public:
		void write_exception( Axe::ArchiveWrite & _ar, std::size_t _methodId, const Axe::Exception & _ex );
	
	private:
		void callMethod( std::size_t _methodId , std::size_t _requestId , const Axe::SessionPtr & _session ) override;
		void responseException( std::size_t _methodId, std::size_t _requestId, const SessionPtr & _session, const Exception & _ex ) override;
	};
	
	typedef AxeHandle<Servant_GridManager> Servant_GridManagerPtr;
	
	void operator << ( Axe::ArchiveWrite & _ar, const Servant_GridManagerPtr & _value );
	
	
	class Bellhop_GridManager_addAdapter
		: public Axe::Bellhop
	{
	public:
		Bellhop_GridManager_addAdapter( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_GridManagerPtr & _servant );
	
	public:
		void response( std::size_t );
	
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_GridManagerPtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_GridManager_addAdapter> Bellhop_GridManager_addAdapterPtr;
	class Bellhop_GridManager_getAdapterEndpoint
		: public Axe::Bellhop
	{
	public:
		Bellhop_GridManager_getAdapterEndpoint( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_GridManagerPtr & _servant );
	
	public:
		void response( const std::string & );
	
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_GridManagerPtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_GridManager_getAdapterEndpoint> Bellhop_GridManager_getAdapterEndpointPtr;
	class Bellhop_GridManager_addUnique
		: public Axe::Bellhop
	{
	public:
		Bellhop_GridManager_addUnique( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_GridManagerPtr & _servant );
	
	public:
		void response();
	
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_GridManagerPtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_GridManager_addUnique> Bellhop_GridManager_addUniquePtr;
	class Bellhop_GridManager_getUnique
		: public Axe::Bellhop
	{
	public:
		Bellhop_GridManager_getUnique( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_GridManagerPtr & _servant );
	
	public:
		void response( const Proxy_UniquePtr & );
	
		void throw_exception( const Axe::Exception & _ex );
	
	protected:
		Servant_GridManagerPtr m_servant;
	};
	
	typedef AxeHandle<Bellhop_GridManager_getUnique> Bellhop_GridManager_getUniquePtr;
	
	//////////////////////////////////////////////////////////////////////////
	class Response_GridManager_addAdapter
		: public Axe::Response
	{
	protected:
		virtual void response( std::size_t ) = 0;
	
	public:
		void responseCall( Axe::ArchiveRead & _ar, std::size_t _size ) override;
		void exceptionCall( Axe::ArchiveRead & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_GridManager_addAdapter> Response_GridManager_addAdapterPtr;
	
	template<>
	class BindResponse<Response_GridManager_addAdapterPtr>
		: public Response_GridManager_addAdapter
	{
		typedef boost::function<void(std::size_t)> TBindResponse;
		typedef boost::function<void(const Axe::Exception &)> TBindException;
	
	public:
		BindResponse( const TBindResponse & _response, const TBindException & _exception );
	
	public:
		void response( std::size_t _arg0 ) override;
	
		void throw_exception( const Axe::Exception & _ex ) override;
	
	protected:
		TBindResponse m_response;
		TBindException m_exception;
	};
	//////////////////////////////////////////////////////////////////////////
	class Response_GridManager_getAdapterEndpoint
		: public Axe::Response
	{
	protected:
		virtual void response( const std::string & ) = 0;
	
	public:
		void responseCall( Axe::ArchiveRead & _ar, std::size_t _size ) override;
		void exceptionCall( Axe::ArchiveRead & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_GridManager_getAdapterEndpoint> Response_GridManager_getAdapterEndpointPtr;
	
	template<>
	class BindResponse<Response_GridManager_getAdapterEndpointPtr>
		: public Response_GridManager_getAdapterEndpoint
	{
		typedef boost::function<void(const std::string &)> TBindResponse;
		typedef boost::function<void(const Axe::Exception &)> TBindException;
	
	public:
		BindResponse( const TBindResponse & _response, const TBindException & _exception );
	
	public:
		void response( const std::string & _arg0 ) override;
	
		void throw_exception( const Axe::Exception & _ex ) override;
	
	protected:
		TBindResponse m_response;
		TBindException m_exception;
	};
	//////////////////////////////////////////////////////////////////////////
	class Response_GridManager_addUnique
		: public Axe::Response
	{
	protected:
		virtual void response() = 0;
	
	public:
		void responseCall( Axe::ArchiveRead & _ar, std::size_t _size ) override;
		void exceptionCall( Axe::ArchiveRead & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_GridManager_addUnique> Response_GridManager_addUniquePtr;
	
	template<>
	class BindResponse<Response_GridManager_addUniquePtr>
		: public Response_GridManager_addUnique
	{
		typedef boost::function<void()> TBindResponse;
		typedef boost::function<void(const Axe::Exception &)> TBindException;
	
	public:
		BindResponse( const TBindResponse & _response, const TBindException & _exception );
	
	public:
		void response() override;
	
		void throw_exception( const Axe::Exception & _ex ) override;
	
	protected:
		TBindResponse m_response;
		TBindException m_exception;
	};
	//////////////////////////////////////////////////////////////////////////
	class Response_GridManager_getUnique
		: public Axe::Response
	{
	protected:
		virtual void response( const Proxy_UniquePtr & ) = 0;
	
	public:
		void responseCall( Axe::ArchiveRead & _ar, std::size_t _size ) override;
		void exceptionCall( Axe::ArchiveRead & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_GridManager_getUnique> Response_GridManager_getUniquePtr;
	
	template<>
	class BindResponse<Response_GridManager_getUniquePtr>
		: public Response_GridManager_getUnique
	{
		typedef boost::function<void(const Proxy_UniquePtr &)> TBindResponse;
		typedef boost::function<void(const Axe::Exception &)> TBindException;
	
	public:
		BindResponse( const TBindResponse & _response, const TBindException & _exception );
	
	public:
		void response( const Proxy_UniquePtr & _arg0 ) override;
	
		void throw_exception( const Axe::Exception & _ex ) override;
	
	protected:
		TBindResponse m_response;
		TBindException m_exception;
	};
	
	class Proxy_GridManager
		: virtual public Axe::Proxy
	{
	public:
		Proxy_GridManager( std::size_t _id, const Axe::ConnectionPtr & _connection );
	
	public:
		void addAdapter( const Response_GridManager_addAdapterPtr & _response, const std::string & _name, const std::string & _endpoint );
		void getAdapterEndpoint( const Response_GridManager_getAdapterEndpointPtr & _response, std::size_t _hostId );
		void addUnique( const Response_GridManager_addUniquePtr & _response, const std::string & _name, const Proxy_UniquePtr & _unique );
		void getUnique( const Response_GridManager_getUniquePtr & _response, const std::string & _name );
	};
	
	typedef AxeHandle<Proxy_GridManager> Proxy_GridManagerPtr;
	
	void operator << ( Axe::ArchiveWrite & _ar, const Proxy_GridManagerPtr & _value );
}
