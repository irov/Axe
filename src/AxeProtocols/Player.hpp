#	pragma once

#	include <Axe/Bellhop.hpp>
#	include <Axe/Servant.hpp>
#	include <Axe/Response.hpp>
#	include <Axe/Proxy.hpp>
#	include <Axe/Response.hpp>
#	include <Axe/Exception.hpp>

#	include <AxeProtocols/SessionManager.hpp>

namespace Axe
{
	class ArchiveInvocation;
	class ArchiveDispatcher;
}

namespace Axe
{
	
	struct PlayerInfo
	{
		std::string name;
		int id;
	};
	
	
	typedef AxeHandle<class Bellhop_Player_test> Bellhop_Player_testPtr;
	
	class Servant_Player
		: public ::Axe::Servant_Session
	{
	public:
		static const std::string & getTypeId();
	
	public:
		virtual void test_async( const Bellhop_Player_testPtr & _cb, const PlayerInfo & info ) = 0;
	
	public:
		void callMethod( std::size_t _methodId , std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session ) override;
		void responseException( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const Axe::Exception & _ex ) override;
	public:
		void writeExceptions_( std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
	};
	
	typedef AxeHandle<Servant_Player> Servant_PlayerPtr;
	
	
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
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};
	
	typedef AxeHandle<Response_Player_test> Response_Player_testPtr;
	
	class Proxy_Player
		:	public ::Axe::Proxy_Session
	{
	public:
		Proxy_Player( std::size_t _id, const Axe::ProxyAdapterProviderPtr & _adapterProvider );
	
	public:
		void test_async( const Response_Player_testPtr & _response, const PlayerInfo & info );
	};
	
	typedef AxeHandle<Proxy_Player> Proxy_PlayerPtr;
}
namespace Axe
{
	void operator << ( Axe::ArchiveInvocation & ar, const ::Axe::PlayerInfo & _value );
	void operator >> ( Axe::ArchiveDispatcher & ar, ::Axe::PlayerInfo & _value );
	
	template<>
	class BindResponse<::Axe::Response_Player_testPtr>
		: public BindResponseHelper<::Axe::Response_Player_test, void(int)>
	{
	protected:
		typedef BindResponseHelper<::Axe::Response_Player_test, void(int)> TBaseHelper;
	
	public:
		BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception );
	
	public:
		void response( int _arg0 ) override;
	};
	
	void operator << ( Axe::ArchiveInvocation & _ar, const ::Axe::Proxy_PlayerPtr & _value );
}
