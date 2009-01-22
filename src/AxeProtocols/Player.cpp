#	include <Axe/pch.hpp>

#	include "Player.hpp"

#	include <Axe/ArchiveWrite.hpp>
#	include <Axe/ArchiveRead.hpp>

namespace Axe
{
	
	//////////////////////////////////////////////////////////////////////////
	Bellhop_Player_test::Bellhop_Player_test( std::size_t _requestId, const Axe::AdapterSessionPtr & _session )
		: Axe::Bellhop(_requestId, _session)
	{
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_Player_test::response( int _arg0 )
	{
		Axe::ArchiveWrite & ar = m_session->beginResponse( m_requestId );
		ar << _arg0;
		m_session->process();
	}
	
	enum
	{
		ESMD_Player = 0
		,	ESMD_Player_test
	};
	
	//////////////////////////////////////////////////////////////////////////
	void Servant_Player::callMethod( std::size_t _methodId, std::size_t _requestId, const Axe::AdapterSessionPtr & _session, const ConnectionCachePtr & _connectionCache )
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
	void Response_Player_test::responseCall( Axe::ArchiveRead & _ar )
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
	
		this->process();
	}
	
}
