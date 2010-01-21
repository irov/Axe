#	include "pch.hpp"

#	include "Player.hpp"

#	include <Axe/ArchiveInvocation.hpp>
#	include <Axe/ArchiveDispatcher.hpp>
#	include <Axe/ProxyAdapterProvider.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	static std::string s_servant_type_Servant_Player = "::Axe::Servant_Player";
	//////////////////////////////////////////////////////////////////////////
	const std::string & Servant_Player::getTypeId()
	{
		return s_servant_type_Servant_Player;
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_Player_callMethod_test( Servant_Player * _servant, std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_Player_testPtr bellhop = new Bellhop_Player_test( _requestId, _session, _servant );
	
		PlayerInfo arg0; _archive >> arg0;
	
		_servant->test_async( bellhop, arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_Player_subMethod_Session_callMethod( Servant_Player * _servant, std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		static_cast<::Axe::Servant_Session *>(_servant)->callMethod( _methodId, _requestId, _archive, _session );
	}
	static void s_Servant_Player_dummyMethod( Servant_Player * _servant, std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		static_cast<Axe::Servant *>( _servant )->callMethod( _methodId, _requestId, _archive, _session );
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_Player_callMethod)( Servant_Player * _servant, std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session );
	//////////////////////////////////////////////////////////////////////////
	static TServant_Player_callMethod s_Servant_Player_callMethods[] =
	{
		&s_Servant_Player_dummyMethod
		, &s_Servant_Player_subMethod_Session_callMethod
		, &s_Servant_Player_callMethod_test
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_Player::callMethod( std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		(*s_Servant_Player_callMethods[ _methodId ])( this, _methodId, _requestId, _archive, _session );
	}
	static void s_Servant_Player_subMethod_Session_writeException( Servant_Player * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		static_cast<::Axe::Servant_Session *>( _servant )->writeExceptions_( _methodId, _ar, _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_Player_writeException_test( Servant_Player * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		Axe::writeExceptionFilter( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_Player_writeException)( Servant_Player * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
	//////////////////////////////////////////////////////////////////////////
	static TServant_Player_writeException s_Servant_Player_writeExceptions[] =
	{
		0
		, &s_Servant_Player_subMethod_Session_writeException
		, &s_Servant_Player_writeException_test
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_Player::responseException( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & aw = _session->beginException( _requestId );
	
		this->writeExceptions_( _methodId, aw, _ex );
	
		_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant_Player::writeExceptions_( std::size_t _methodId, Axe::ArchiveInvocation & _aw, const Axe::Exception & _ex )
	{
		(*s_Servant_Player_writeExceptions[ _methodId ])( this, _methodId, _aw, _ex );
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
		Axe::ArchiveInvocation & ar = this->beginResponse();
		ar << _arg0;
		this->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_Player_test::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = this->beginException();
		s_Servant_Player_writeException_test( AxeUtil::nativePtr(m_servant), 4, ar, _ex );
		this->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_Player_test::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		int arg0; _ar >> arg0;
		this->response( arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	Proxy_Player::Proxy_Player( std::size_t _id, const Axe::ProxyAdapterProviderPtr & _adapterProvider )
		: Axe::Proxy(_id, _adapterProvider)
		, ::Axe::Proxy_Session(_id, _adapterProvider)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_Player::test_async( const Response_Player_testPtr & _response, const PlayerInfo & info )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 2, _response );
		ar << info;
	
		this->processMessage();
	}
}
namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & ar, const ::Axe::PlayerInfo & _value )
	{
		ar << _value.name;
		ar << _value.id;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator >> ( Axe::ArchiveDispatcher & ar, ::Axe::PlayerInfo & _value )
	{
		ar >> _value.name;
		ar >> _value.id;
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<::Axe::Response_Player_testPtr>::BindResponse( const TBaseHelper::TBindResponse & _response, const TBaseHelper::TBindException & _exception )
		: TBaseHelper(_response,_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<::Axe::Response_Player_testPtr>::response( int _arg0 )
	{
		m_response( _arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & _ar, const ::Axe::Proxy_PlayerPtr & _value )
	{
		_value->write( _ar );
	}
}
