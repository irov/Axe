#	include "pch.hpp"

#	include "Player.hpp"

#	include <Axe/ArchiveInvocation.hpp>
#	include <Axe/ArchiveDispatcher.hpp>

namespace Axe
{
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
		, Proxy_Session(_id, _connection)
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
}
