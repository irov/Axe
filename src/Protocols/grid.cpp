#	include <Axe/pch.hpp>

#	include "grid.hpp"

#	include <Axe/ArchiveWrite.hpp>
#	include <Axe/ArchiveRead.hpp>

namespace Protocol
{
	
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveWrite & ar, const base_info & _value )
	{
		ar << _value.id;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator >> ( Axe::ArchiveRead & ar, base_info & _value )
	{
		ar >> _value.id;
	}
	
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveWrite & ar, const servant_info & _value )
	{
		ar << static_cast<const base_info &>( _value );
		ar << _value.enpoint;
		ar << _value.id;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator >> ( Axe::ArchiveRead & ar, servant_info & _value )
	{
		ar >> static_cast<const base_info &>( _value );
		ar >> _value.enpoint;
		ar >> _value.id;
	}
	
	//////////////////////////////////////////////////////////////////////////
	Bellhop_grid_get_servand_endpoint::Bellhop_grid_get_servand_endpoint( std::size_t _requestId, const Axe::AdapterSessionPtr & _session )
		: Axe::Bellhop(_requestId, _session)
	{
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_grid_get_servand_endpoint::response( const servant_info & _arg0 )
	{
		Axe::ArchiveWrite & ar = m_session->beginResponse( m_requestId );
		ar << _arg0;
		m_session->process();
	}
	
	enum
	{
		ESMD_grid = 0
		,	ESMD_grid_get_servand_endpoint
	};
	
	//////////////////////////////////////////////////////////////////////////
	void Servant_grid::callMethod( std::size_t _methodId, std::size_t _requestId, const Axe::AdapterSessionPtr & _session, const ConnectionCachePtr & _connectionCache )
	{
		Axe::ArchiveRead & ar = _session->getArchiveRead();
		switch( _methodId )
		{
		case ESMD_grid_get_servand_endpoint:
			{
				Bellhop_grid_get_servand_endpointPtr bellhop = new Bellhop_grid_get_servand_endpoint( _requestId, _session );
	
				std::string arg0; ar >> arg0;
				vector_int arg1; ar >> arg1;
				this->get_servand_endpoint( bellhop, arg0, arg1 );
			}break;
		}
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Response_grid_get_servand_endpoint::responseCall( Axe::ArchiveRead & _ar, const ConnectionCachePtr & _connectionCache )
	{
		servant_info arg0; _ar >> arg0;
		this->response( arg0 );
	}
	
	//////////////////////////////////////////////////////////////////////////
	Proxy_grid::Proxy_grid( std::size_t _id, const Axe::ConnectionPtr & _connection )
		: Axe::Proxy(_id, _connection)
	{
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Proxy_grid::get_servand_endpoint( const std::string & _name, const vector_int & vec, const Response_grid_get_servand_endpointPtr & _response )
	{
		Axe::ArchiveWrite & ar = this->beginMessage( ESMD_grid_get_servand_endpoint, _response );
		ar << _name;
		ar << vec;
	
		this->process();
	}
	
	
	//////////////////////////////////////////////////////////////////////////
	Bellhop_box_add::Bellhop_box_add( std::size_t _requestId, const Axe::AdapterSessionPtr & _session )
		: Axe::Bellhop(_requestId, _session)
	{
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_box_add::response()
	{
		Axe::ArchiveWrite & ar = m_session->beginResponse( m_requestId );
		m_session->process();
	}
	
	enum
	{
		ESMD_box = 0
		,	ESMD_box_add
	};
	
	//////////////////////////////////////////////////////////////////////////
	void Servant_box::callMethod( std::size_t _methodId, std::size_t _requestId, const Axe::AdapterSessionPtr & _session, const ConnectionCachePtr & _connectionCache )
	{
		Axe::ArchiveRead & ar = _session->getArchiveRead();
		switch( _methodId )
		{
		case ESMD_box_add:
			{
				Bellhop_box_addPtr bellhop = new Bellhop_box_add( _requestId, _session );
	
				this->add( bellhop );
			}break;
		}
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Response_box_add::responseCall( Axe::ArchiveRead & _ar, const ConnectionCachePtr & _connectionCache )
	{
		this->response();
	}
	
	//////////////////////////////////////////////////////////////////////////
	Proxy_box::Proxy_box( std::size_t _id, const Axe::ConnectionPtr & _connection )
		: Axe::Proxy(_id, _connection)
		, Proxy_grid(_id, _connection)
	{
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Proxy_box::add( const Response_box_addPtr & _response )
	{
		Axe::ArchiveWrite & ar = this->beginMessage( ESMD_box_add, _response );
	
		this->process();
	}
	
	
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveWrite & ar, const vec2f & _value )
	{
		ar << _value.x;
		ar << _value.y;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator >> ( Axe::ArchiveRead & ar, vec2f & _value )
	{
		ar >> _value.x;
		ar >> _value.y;
	}
	
	//////////////////////////////////////////////////////////////////////////
	Bellhop_Player_moveTo::Bellhop_Player_moveTo( std::size_t _requestId, const Axe::AdapterSessionPtr & _session )
		: Axe::Bellhop(_requestId, _session)
	{
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_Player_moveTo::response()
	{
		Axe::ArchiveWrite & ar = m_session->beginResponse( m_requestId );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_Player_teleportTo::Bellhop_Player_teleportTo( std::size_t _requestId, const Axe::AdapterSessionPtr & _session )
		: Axe::Bellhop(_requestId, _session)
	{
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_Player_teleportTo::response()
	{
		Axe::ArchiveWrite & ar = m_session->beginResponse( m_requestId );
		m_session->process();
	}
	
	enum
	{
		ESMD_Player = 0
		,	ESMD_Player_moveTo
		,	ESMD_Player_teleportTo
	};
	
	//////////////////////////////////////////////////////////////////////////
	void Servant_Player::callMethod( std::size_t _methodId, std::size_t _requestId, const Axe::AdapterSessionPtr & _session, const ConnectionCachePtr & _connectionCache )
	{
		Axe::ArchiveRead & ar = _session->getArchiveRead();
		switch( _methodId )
		{
		case ESMD_Player_moveTo:
			{
				Bellhop_Player_moveToPtr bellhop = new Bellhop_Player_moveTo( _requestId, _session );
	
				vec2f arg0; ar >> arg0;
				this->moveTo( bellhop, arg0 );
			}break;
		case ESMD_Player_teleportTo:
			{
				Bellhop_Player_teleportToPtr bellhop = new Bellhop_Player_teleportTo( _requestId, _session );
	
				vec2f arg0; ar >> arg0;
				this->teleportTo( bellhop, arg0 );
			}break;
		}
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Response_Player_moveTo::responseCall( Axe::ArchiveRead & _ar, const ConnectionCachePtr & _connectionCache )
	{
		this->response();
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_Player_teleportTo::responseCall( Axe::ArchiveRead & _ar, const ConnectionCachePtr & _connectionCache )
	{
		this->response();
	}
	
	//////////////////////////////////////////////////////////////////////////
	Proxy_Player::Proxy_Player( std::size_t _id, const Axe::ConnectionPtr & _connection )
		: Axe::Proxy(_id, _connection)
	{
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Proxy_Player::moveTo( const vec2f & _vec, const Response_Player_moveToPtr & _response )
	{
		Axe::ArchiveWrite & ar = this->beginMessage( ESMD_Player_moveTo, _response );
		ar << _vec;
	
		this->process();
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Proxy_Player::teleportTo( const vec2f & _vec, const Response_Player_teleportToPtr & _response )
	{
		Axe::ArchiveWrite & ar = this->beginMessage( ESMD_Player_teleportTo, _response );
		ar << _vec;
	
		this->process();
	}
	
	
	//////////////////////////////////////////////////////////////////////////
	Bellhop_Client_onConnect::Bellhop_Client_onConnect( std::size_t _requestId, const Axe::AdapterSessionPtr & _session )
		: Axe::Bellhop(_requestId, _session)
	{
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_Client_onConnect::response()
	{
		Axe::ArchiveWrite & ar = m_session->beginResponse( m_requestId );
		m_session->process();
	}
	
	enum
	{
		ESMD_Client = 0
		,	ESMD_Client_onConnect
	};
	
	//////////////////////////////////////////////////////////////////////////
	void Servant_Client::callMethod( std::size_t _methodId, std::size_t _requestId, const Axe::AdapterSessionPtr & _session, const ConnectionCachePtr & _connectionCache )
	{
		Axe::ArchiveRead & ar = _session->getArchiveRead();
		switch( _methodId )
		{
		case ESMD_Client_onConnect:
			{
				Bellhop_Client_onConnectPtr bellhop = new Bellhop_Client_onConnect( _requestId, _session );
	
				Proxy_PlayerPtr arg0 = makeProxy<Proxy_Player>( ar, _connectionCache );
				this->onConnect( bellhop, arg0 );
			}break;
		}
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Response_Client_onConnect::responseCall( Axe::ArchiveRead & _ar, const ConnectionCachePtr & _connectionCache )
	{
		this->response();
	}
	
	//////////////////////////////////////////////////////////////////////////
	Proxy_Client::Proxy_Client( std::size_t _id, const Axe::ConnectionPtr & _connection )
		: Axe::Proxy(_id, _connection)
	{
	}
	
	//////////////////////////////////////////////////////////////////////////
	void Proxy_Client::onConnect( const Proxy_PlayerPtr & _player, const Response_Client_onConnectPtr & _response )
	{
		Axe::ArchiveWrite & ar = this->beginMessage( ESMD_Client_onConnect, _response );
		ar << _player;
	
		this->process();
	}
	
}
