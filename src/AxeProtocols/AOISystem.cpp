#	include "pch.hpp"

#	include "AOISystem.hpp"

#	include <Axe/ArchiveInvocation.hpp>
#	include <Axe/ArchiveDispatcher.hpp>
#	include <Axe/ProxyHostProvider.hpp>

namespace AxeLibProtocol
{
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & ar, const AOIPropagateAddAvatar & _value )
	{
		ar << _value.userId;
		ar << _value.typeId;
		ar << _value.pos;
		ar << _value.dir;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator >> ( Axe::ArchiveDispatcher & ar, AOIPropagateAddAvatar & _value )
	{
		ar >> _value.userId;
		ar >> _value.typeId;
		ar >> _value.pos;
		ar >> _value.dir;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & ar, const AOIPropagateRemoveAvatar & _value )
	{
		ar << _value.userId;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator >> ( Axe::ArchiveDispatcher & ar, AOIPropagateRemoveAvatar & _value )
	{
		ar >> _value.userId;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & ar, const AOIPropagateMoveAvatar & _value )
	{
		ar << _value.userId;
		ar << _value.steps;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator >> ( Axe::ArchiveDispatcher & ar, AOIPropagateMoveAvatar & _value )
	{
		ar >> _value.userId;
		ar >> _value.steps;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & ar, const AOIPropagateDiffAvatar & _value )
	{
		ar << _value.add;
		ar << _value.move;
		ar << _value.remove;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator >> ( Axe::ArchiveDispatcher & ar, AOIPropagateDiffAvatar & _value )
	{
		ar >> _value.add;
		ar >> _value.move;
		ar >> _value.remove;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & ar, const AOIAvatarDesc & _value )
	{
		ar << _value.typeId;
		ar << _value.desc;
		ar << _value.radius;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator >> ( Axe::ArchiveDispatcher & ar, AOIAvatarDesc & _value )
	{
		ar >> _value.typeId;
		ar >> _value.desc;
		ar >> _value.radius;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & ar, const AOIAvatarMoveDesc & _value )
	{
		ar << _value.desc;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator >> ( Axe::ArchiveDispatcher & ar, AOIAvatarMoveDesc & _value )
	{
		ar >> _value.desc;
	}
	//////////////////////////////////////////////////////////////////////////
	void s_Servant_AOITile_callMethod_insertAvatar( Servant_AOITile * _servant, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_AOITile_insertAvatarPtr bellhop = new Bellhop_AOITile_insertAvatar( _requestId, _session, _servant );
	
		int arg0; _archive >> arg0;
		AOIAvatarDesc arg1; _archive >> arg1;
		bool arg2; _archive >> arg2;
	
		_servant->insertAvatar_async( bellhop, arg0, arg1, arg2 );
	}
	//////////////////////////////////////////////////////////////////////////
	void s_Servant_AOITile_callMethod_removeAvatar( Servant_AOITile * _servant, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_AOITile_removeAvatarPtr bellhop = new Bellhop_AOITile_removeAvatar( _requestId, _session, _servant );
	
		int arg0; _archive >> arg0;
	
		_servant->removeAvatar_async( bellhop, arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void s_Servant_AOITile_callMethod_moveAvatar( Servant_AOITile * _servant, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_AOITile_moveAvatarPtr bellhop = new Bellhop_AOITile_moveAvatar( _requestId, _session, _servant );
	
		AOIAvatarMoveDesc arg0; _archive >> arg0;
	
		_servant->moveAvatar_async( bellhop, arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void s_Servant_AOITile_callMethod_updateAvatar( Servant_AOITile * _servant, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_AOITile_updateAvatarPtr bellhop = new Bellhop_AOITile_updateAvatar( _requestId, _session, _servant );
	
		int arg0; _archive >> arg0;
	
		_servant->updateAvatar_async( bellhop, arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_AOITile_callMethod)( Servant_AOITile * _servant, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session );
	//////////////////////////////////////////////////////////////////////////
	static TServant_AOITile_callMethod s_Servant_AOITile_callMethods[] =
	{
		0
		, &s_Servant_AOITile_callMethod_insertAvatar
		, &s_Servant_AOITile_callMethod_removeAvatar
		, &s_Servant_AOITile_callMethod_moveAvatar
		, &s_Servant_AOITile_callMethod_updateAvatar
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_AOITile::callMethod( std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		(*s_Servant_AOITile_callMethods[ _methodId ])( this, _methodId, _requestId, _archive, _session );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_AOITile_writeException_insertAvatar( Servant_AOITile * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		Axe::writeExceptionFilter( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_AOITile_writeException_removeAvatar( Servant_AOITile * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		Axe::writeExceptionFilter( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_AOITile_writeException_moveAvatar( Servant_AOITile * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		Axe::writeExceptionFilter( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_AOITile_writeException_updateAvatar( Servant_AOITile * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		Axe::writeExceptionFilter( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_AOITile_writeException)( Servant_AOITile * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
	//////////////////////////////////////////////////////////////////////////
	static TServant_AOITile_writeException s_Servant_AOITile_writeExceptions[] =
	{
		0
		, &s_Servant_AOITile_writeException_insertAvatar
		, &s_Servant_AOITile_writeException_removeAvatar
		, &s_Servant_AOITile_writeException_moveAvatar
		, &s_Servant_AOITile_writeException_updateAvatar
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_AOITile::responseException( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & aw = _session->beginException( _requestId );
	
		this->writeExceptions_( _methodId, aw, _ex );
	
		_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant_AOITile::writeExceptions_( std::size_t _methodId, Axe::ArchiveInvocation & _aw, const Axe::Exception & _ex )
	{
		(*s_Servant_AOITile_writeExceptions[ _methodId ])( this, _methodId, _aw, _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_AOITile_insertAvatar::Bellhop_AOITile_insertAvatar( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_AOITilePtr & _servant )
		: Axe::Bellhop(_requestId, _session)
		, m_servant(_servant)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_AOITile_insertAvatar::response( int _arg0 )
	{
		Axe::ArchiveInvocation & ar = m_session->beginResponse( m_requestId );
		ar << _arg0;
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_AOITile_insertAvatar::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = m_session->beginException( m_requestId );
		s_Servant_AOITile_writeException_insertAvatar( AxeUtil::nativePtr(m_servant), 3, ar, _ex );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_AOITile_removeAvatar::Bellhop_AOITile_removeAvatar( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_AOITilePtr & _servant )
		: Axe::Bellhop(_requestId, _session)
		, m_servant(_servant)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_AOITile_removeAvatar::response()
	{
		Axe::ArchiveInvocation & ar = m_session->beginResponse( m_requestId );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_AOITile_removeAvatar::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = m_session->beginException( m_requestId );
		s_Servant_AOITile_writeException_removeAvatar( AxeUtil::nativePtr(m_servant), 4, ar, _ex );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_AOITile_moveAvatar::Bellhop_AOITile_moveAvatar( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_AOITilePtr & _servant )
		: Axe::Bellhop(_requestId, _session)
		, m_servant(_servant)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_AOITile_moveAvatar::response()
	{
		Axe::ArchiveInvocation & ar = m_session->beginResponse( m_requestId );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_AOITile_moveAvatar::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = m_session->beginException( m_requestId );
		s_Servant_AOITile_writeException_moveAvatar( AxeUtil::nativePtr(m_servant), 5, ar, _ex );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_AOITile_updateAvatar::Bellhop_AOITile_updateAvatar( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_AOITilePtr & _servant )
		: Axe::Bellhop(_requestId, _session)
		, m_servant(_servant)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_AOITile_updateAvatar::response( const AOIPropagateDiffAvatar & _arg0 )
	{
		Axe::ArchiveInvocation & ar = m_session->beginResponse( m_requestId );
		ar << _arg0;
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_AOITile_updateAvatar::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = m_session->beginException( m_requestId );
		s_Servant_AOITile_writeException_updateAvatar( AxeUtil::nativePtr(m_servant), 6, ar, _ex );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<Response_AOITile_insertAvatarPtr>::BindResponse( const TBindResponse & _response, const TBindException & _exception )
		: m_response(_response)
		, m_exception(_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_AOITile_insertAvatarPtr>::response( int _arg0 )
	{
		m_response( _arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_AOITile_insertAvatarPtr>::throw_exception( const Axe::Exception & _ex )
	{
		m_exception( _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_AOITile_insertAvatar::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		int arg0; _ar >> arg0;
		this->response( arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_AOITile_insertAvatar::exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		std::size_t exceptionId;
		_ar.readSize( exceptionId );
	
		if( this->exceptionFilter( exceptionId, _ar ) == true )
		{
			return;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<Response_AOITile_removeAvatarPtr>::BindResponse( const TBindResponse & _response, const TBindException & _exception )
		: m_response(_response)
		, m_exception(_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_AOITile_removeAvatarPtr>::response()
	{
		m_response();
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_AOITile_removeAvatarPtr>::throw_exception( const Axe::Exception & _ex )
	{
		m_exception( _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_AOITile_removeAvatar::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		this->response();
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_AOITile_removeAvatar::exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		std::size_t exceptionId;
		_ar.readSize( exceptionId );
	
		if( this->exceptionFilter( exceptionId, _ar ) == true )
		{
			return;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<Response_AOITile_moveAvatarPtr>::BindResponse( const TBindResponse & _response, const TBindException & _exception )
		: m_response(_response)
		, m_exception(_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_AOITile_moveAvatarPtr>::response()
	{
		m_response();
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_AOITile_moveAvatarPtr>::throw_exception( const Axe::Exception & _ex )
	{
		m_exception( _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_AOITile_moveAvatar::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		this->response();
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_AOITile_moveAvatar::exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		std::size_t exceptionId;
		_ar.readSize( exceptionId );
	
		if( this->exceptionFilter( exceptionId, _ar ) == true )
		{
			return;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<Response_AOITile_updateAvatarPtr>::BindResponse( const TBindResponse & _response, const TBindException & _exception )
		: m_response(_response)
		, m_exception(_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_AOITile_updateAvatarPtr>::response( const AOIPropagateDiffAvatar & _arg0 )
	{
		m_response( _arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_AOITile_updateAvatarPtr>::throw_exception( const Axe::Exception & _ex )
	{
		m_exception( _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_AOITile_updateAvatar::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		AOIPropagateDiffAvatar arg0; _ar >> arg0;
		this->response( arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_AOITile_updateAvatar::exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		std::size_t exceptionId;
		_ar.readSize( exceptionId );
	
		if( this->exceptionFilter( exceptionId, _ar ) == true )
		{
			return;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	Proxy_AOITile::Proxy_AOITile( std::size_t _id, const Axe::ProxyHostProviderPtr & _hostProvider )
		: Axe::Proxy(_id, _hostProvider)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_AOITile::insertAvatar_async( const Response_AOITile_insertAvatarPtr & _response, int _userId, const AOIAvatarDesc & _desc, bool _master )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 1, _response );
		ar << _userId;
		ar << _desc;
		ar << _master;
	
		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_AOITile::removeAvatar_async( const Response_AOITile_removeAvatarPtr & _response, int _avatarId )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 2, _response );
		ar << _avatarId;
	
		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_AOITile::moveAvatar_async( const Response_AOITile_moveAvatarPtr & _response, const AOIAvatarMoveDesc & _desc )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 3, _response );
		ar << _desc;
	
		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_AOITile::updateAvatar_async( const Response_AOITile_updateAvatarPtr & _response, int _avatarId )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 4, _response );
		ar << _avatarId;
	
		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & _ar, const Proxy_AOITilePtr & _value )
	{
		_value->write( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	void s_Servant_AOITileFactory_callMethod_createTile( Servant_AOITileFactory * _servant, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_AOITileFactory_createTilePtr bellhop = new Bellhop_AOITileFactory_createTile( _requestId, _session, _servant );
	
	
		_servant->createTile_async( bellhop );
	}
	//////////////////////////////////////////////////////////////////////////
	void s_Servant_AOITileFactory_callMethod_destroyTile( Servant_AOITileFactory * _servant, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_AOITileFactory_destroyTilePtr bellhop = new Bellhop_AOITileFactory_destroyTile( _requestId, _session, _servant );
	
		Proxy_AOITilePtr arg0; _archive >> arg0;
	
		_servant->destroyTile_async( bellhop, arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_AOITileFactory_callMethod)( Servant_AOITileFactory * _servant, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session );
	//////////////////////////////////////////////////////////////////////////
	static TServant_AOITileFactory_callMethod s_Servant_AOITileFactory_callMethods[] =
	{
		0
		, &s_Servant_AOITileFactory_callMethod_createTile
		, &s_Servant_AOITileFactory_callMethod_destroyTile
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_AOITileFactory::callMethod( std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		(*s_Servant_AOITileFactory_callMethods[ _methodId ])( this, _methodId, _requestId, _archive, _session );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_AOITileFactory_writeException_createTile( Servant_AOITileFactory * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		Axe::writeExceptionFilter( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_AOITileFactory_writeException_destroyTile( Servant_AOITileFactory * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		Axe::writeExceptionFilter( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_AOITileFactory_writeException)( Servant_AOITileFactory * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
	//////////////////////////////////////////////////////////////////////////
	static TServant_AOITileFactory_writeException s_Servant_AOITileFactory_writeExceptions[] =
	{
		0
		, &s_Servant_AOITileFactory_writeException_createTile
		, &s_Servant_AOITileFactory_writeException_destroyTile
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_AOITileFactory::responseException( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & aw = _session->beginException( _requestId );
	
		this->writeExceptions_( _methodId, aw, _ex );
	
		_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant_AOITileFactory::writeExceptions_( std::size_t _methodId, Axe::ArchiveInvocation & _aw, const Axe::Exception & _ex )
	{
		(*s_Servant_AOITileFactory_writeExceptions[ _methodId ])( this, _methodId, _aw, _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_AOITileFactory_createTile::Bellhop_AOITileFactory_createTile( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_AOITileFactoryPtr & _servant )
		: Axe::Bellhop(_requestId, _session)
		, m_servant(_servant)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_AOITileFactory_createTile::response( const Proxy_AOITilePtr & _arg0 )
	{
		Axe::ArchiveInvocation & ar = m_session->beginResponse( m_requestId );
		ar << _arg0;
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_AOITileFactory_createTile::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = m_session->beginException( m_requestId );
		s_Servant_AOITileFactory_writeException_createTile( AxeUtil::nativePtr(m_servant), 3, ar, _ex );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_AOITileFactory_destroyTile::Bellhop_AOITileFactory_destroyTile( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_AOITileFactoryPtr & _servant )
		: Axe::Bellhop(_requestId, _session)
		, m_servant(_servant)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_AOITileFactory_destroyTile::response()
	{
		Axe::ArchiveInvocation & ar = m_session->beginResponse( m_requestId );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_AOITileFactory_destroyTile::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = m_session->beginException( m_requestId );
		s_Servant_AOITileFactory_writeException_destroyTile( AxeUtil::nativePtr(m_servant), 4, ar, _ex );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<Response_AOITileFactory_createTilePtr>::BindResponse( const TBindResponse & _response, const TBindException & _exception )
		: m_response(_response)
		, m_exception(_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_AOITileFactory_createTilePtr>::response( const Proxy_AOITilePtr & _arg0 )
	{
		m_response( _arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_AOITileFactory_createTilePtr>::throw_exception( const Axe::Exception & _ex )
	{
		m_exception( _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_AOITileFactory_createTile::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		Proxy_AOITilePtr arg0; _ar >> arg0;
		this->response( arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_AOITileFactory_createTile::exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		std::size_t exceptionId;
		_ar.readSize( exceptionId );
	
		if( this->exceptionFilter( exceptionId, _ar ) == true )
		{
			return;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<Response_AOITileFactory_destroyTilePtr>::BindResponse( const TBindResponse & _response, const TBindException & _exception )
		: m_response(_response)
		, m_exception(_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_AOITileFactory_destroyTilePtr>::response()
	{
		m_response();
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_AOITileFactory_destroyTilePtr>::throw_exception( const Axe::Exception & _ex )
	{
		m_exception( _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_AOITileFactory_destroyTile::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		this->response();
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_AOITileFactory_destroyTile::exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		std::size_t exceptionId;
		_ar.readSize( exceptionId );
	
		if( this->exceptionFilter( exceptionId, _ar ) == true )
		{
			return;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	Proxy_AOITileFactory::Proxy_AOITileFactory( std::size_t _id, const Axe::ProxyHostProviderPtr & _hostProvider )
		: Axe::Proxy(_id, _hostProvider)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_AOITileFactory::createTile_async( const Response_AOITileFactory_createTilePtr & _response )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 1, _response );
	
		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_AOITileFactory::destroyTile_async( const Response_AOITileFactory_destroyTilePtr & _response, const Proxy_AOITilePtr & _tileProxy )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 2, _response );
		ar << _tileProxy;
	
		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & _ar, const Proxy_AOITileFactoryPtr & _value )
	{
		_value->write( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	void s_Servant_AOISpace_callMethod_insertAvatar( Servant_AOISpace * _servant, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_AOISpace_insertAvatarPtr bellhop = new Bellhop_AOISpace_insertAvatar( _requestId, _session, _servant );
	
		Axe::ProxyPtr arg0 = Axe::makeProxy<Axe::ProxyPtr>( _archive );
		AOIAvatarDesc arg1; _archive >> arg1;
	
		_servant->insertAvatar_async( bellhop, arg0, arg1 );
	}
	//////////////////////////////////////////////////////////////////////////
	void s_Servant_AOISpace_callMethod_removeAvatar( Servant_AOISpace * _servant, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_AOISpace_removeAvatarPtr bellhop = new Bellhop_AOISpace_removeAvatar( _requestId, _session, _servant );
	
		int arg0; _archive >> arg0;
	
		_servant->removeAvatar_async( bellhop, arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void s_Servant_AOISpace_callMethod_moveAvatar( Servant_AOISpace * _servant, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_AOISpace_moveAvatarPtr bellhop = new Bellhop_AOISpace_moveAvatar( _requestId, _session, _servant );
	
		int arg0; _archive >> arg0;
		AOIAvatarMoveDesc arg1; _archive >> arg1;
	
		_servant->moveAvatar_async( bellhop, arg0, arg1 );
	}
	//////////////////////////////////////////////////////////////////////////
	void s_Servant_AOISpace_callMethod_updateAvatar( Servant_AOISpace * _servant, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_AOISpace_updateAvatarPtr bellhop = new Bellhop_AOISpace_updateAvatar( _requestId, _session, _servant );
	
		int arg0; _archive >> arg0;
	
		_servant->updateAvatar_async( bellhop, arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void s_Servant_AOISpace_callMethod_finalize( Servant_AOISpace * _servant, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_AOISpace_finalizePtr bellhop = new Bellhop_AOISpace_finalize( _requestId, _session, _servant );
	
	
		_servant->finalize_async( bellhop );
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_AOISpace_callMethod)( Servant_AOISpace * _servant, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session );
	//////////////////////////////////////////////////////////////////////////
	static TServant_AOISpace_callMethod s_Servant_AOISpace_callMethods[] =
	{
		0
		, &s_Servant_AOISpace_callMethod_insertAvatar
		, &s_Servant_AOISpace_callMethod_removeAvatar
		, &s_Servant_AOISpace_callMethod_moveAvatar
		, &s_Servant_AOISpace_callMethod_updateAvatar
		, &s_Servant_AOISpace_callMethod_finalize
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_AOISpace::callMethod( std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		(*s_Servant_AOISpace_callMethods[ _methodId ])( this, _methodId, _requestId, _archive, _session );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_AOISpace_writeException_insertAvatar( Servant_AOISpace * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		Axe::writeExceptionFilter( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_AOISpace_writeException_removeAvatar( Servant_AOISpace * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		Axe::writeExceptionFilter( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_AOISpace_writeException_moveAvatar( Servant_AOISpace * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		Axe::writeExceptionFilter( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_AOISpace_writeException_updateAvatar( Servant_AOISpace * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		Axe::writeExceptionFilter( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_AOISpace_writeException_finalize( Servant_AOISpace * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		Axe::writeExceptionFilter( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_AOISpace_writeException)( Servant_AOISpace * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
	//////////////////////////////////////////////////////////////////////////
	static TServant_AOISpace_writeException s_Servant_AOISpace_writeExceptions[] =
	{
		0
		, &s_Servant_AOISpace_writeException_insertAvatar
		, &s_Servant_AOISpace_writeException_removeAvatar
		, &s_Servant_AOISpace_writeException_moveAvatar
		, &s_Servant_AOISpace_writeException_updateAvatar
		, &s_Servant_AOISpace_writeException_finalize
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_AOISpace::responseException( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & aw = _session->beginException( _requestId );
	
		this->writeExceptions_( _methodId, aw, _ex );
	
		_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant_AOISpace::writeExceptions_( std::size_t _methodId, Axe::ArchiveInvocation & _aw, const Axe::Exception & _ex )
	{
		(*s_Servant_AOISpace_writeExceptions[ _methodId ])( this, _methodId, _aw, _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant_AOISpace::_restore( ArchiveDispatcher & _ar )
	{
		_ar >> m_tileProxy;
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant_AOISpace::_evict( ArchiveInvocation & _aw )
	{
		_aw << m_tileProxy;
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_AOISpace_insertAvatar::Bellhop_AOISpace_insertAvatar( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_AOISpacePtr & _servant )
		: Axe::Bellhop(_requestId, _session)
		, m_servant(_servant)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_AOISpace_insertAvatar::response( int _arg0 )
	{
		Axe::ArchiveInvocation & ar = m_session->beginResponse( m_requestId );
		ar << _arg0;
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_AOISpace_insertAvatar::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = m_session->beginException( m_requestId );
		s_Servant_AOISpace_writeException_insertAvatar( AxeUtil::nativePtr(m_servant), 3, ar, _ex );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_AOISpace_removeAvatar::Bellhop_AOISpace_removeAvatar( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_AOISpacePtr & _servant )
		: Axe::Bellhop(_requestId, _session)
		, m_servant(_servant)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_AOISpace_removeAvatar::response()
	{
		Axe::ArchiveInvocation & ar = m_session->beginResponse( m_requestId );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_AOISpace_removeAvatar::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = m_session->beginException( m_requestId );
		s_Servant_AOISpace_writeException_removeAvatar( AxeUtil::nativePtr(m_servant), 4, ar, _ex );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_AOISpace_moveAvatar::Bellhop_AOISpace_moveAvatar( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_AOISpacePtr & _servant )
		: Axe::Bellhop(_requestId, _session)
		, m_servant(_servant)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_AOISpace_moveAvatar::response()
	{
		Axe::ArchiveInvocation & ar = m_session->beginResponse( m_requestId );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_AOISpace_moveAvatar::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = m_session->beginException( m_requestId );
		s_Servant_AOISpace_writeException_moveAvatar( AxeUtil::nativePtr(m_servant), 5, ar, _ex );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_AOISpace_updateAvatar::Bellhop_AOISpace_updateAvatar( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_AOISpacePtr & _servant )
		: Axe::Bellhop(_requestId, _session)
		, m_servant(_servant)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_AOISpace_updateAvatar::response( const AOIPropagateDiffAvatar & _arg0 )
	{
		Axe::ArchiveInvocation & ar = m_session->beginResponse( m_requestId );
		ar << _arg0;
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_AOISpace_updateAvatar::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = m_session->beginException( m_requestId );
		s_Servant_AOISpace_writeException_updateAvatar( AxeUtil::nativePtr(m_servant), 6, ar, _ex );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_AOISpace_finalize::Bellhop_AOISpace_finalize( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_AOISpacePtr & _servant )
		: Axe::Bellhop(_requestId, _session)
		, m_servant(_servant)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_AOISpace_finalize::response( const Proxy_AOITilePtr & _arg0 )
	{
		Axe::ArchiveInvocation & ar = m_session->beginResponse( m_requestId );
		ar << _arg0;
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_AOISpace_finalize::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = m_session->beginException( m_requestId );
		s_Servant_AOISpace_writeException_finalize( AxeUtil::nativePtr(m_servant), 7, ar, _ex );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<Response_AOISpace_insertAvatarPtr>::BindResponse( const TBindResponse & _response, const TBindException & _exception )
		: m_response(_response)
		, m_exception(_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_AOISpace_insertAvatarPtr>::response( int _arg0 )
	{
		m_response( _arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_AOISpace_insertAvatarPtr>::throw_exception( const Axe::Exception & _ex )
	{
		m_exception( _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_AOISpace_insertAvatar::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		int arg0; _ar >> arg0;
		this->response( arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_AOISpace_insertAvatar::exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		std::size_t exceptionId;
		_ar.readSize( exceptionId );
	
		if( this->exceptionFilter( exceptionId, _ar ) == true )
		{
			return;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<Response_AOISpace_removeAvatarPtr>::BindResponse( const TBindResponse & _response, const TBindException & _exception )
		: m_response(_response)
		, m_exception(_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_AOISpace_removeAvatarPtr>::response()
	{
		m_response();
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_AOISpace_removeAvatarPtr>::throw_exception( const Axe::Exception & _ex )
	{
		m_exception( _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_AOISpace_removeAvatar::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		this->response();
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_AOISpace_removeAvatar::exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		std::size_t exceptionId;
		_ar.readSize( exceptionId );
	
		if( this->exceptionFilter( exceptionId, _ar ) == true )
		{
			return;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<Response_AOISpace_moveAvatarPtr>::BindResponse( const TBindResponse & _response, const TBindException & _exception )
		: m_response(_response)
		, m_exception(_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_AOISpace_moveAvatarPtr>::response()
	{
		m_response();
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_AOISpace_moveAvatarPtr>::throw_exception( const Axe::Exception & _ex )
	{
		m_exception( _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_AOISpace_moveAvatar::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		this->response();
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_AOISpace_moveAvatar::exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		std::size_t exceptionId;
		_ar.readSize( exceptionId );
	
		if( this->exceptionFilter( exceptionId, _ar ) == true )
		{
			return;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<Response_AOISpace_updateAvatarPtr>::BindResponse( const TBindResponse & _response, const TBindException & _exception )
		: m_response(_response)
		, m_exception(_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_AOISpace_updateAvatarPtr>::response( const AOIPropagateDiffAvatar & _arg0 )
	{
		m_response( _arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_AOISpace_updateAvatarPtr>::throw_exception( const Axe::Exception & _ex )
	{
		m_exception( _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_AOISpace_updateAvatar::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		AOIPropagateDiffAvatar arg0; _ar >> arg0;
		this->response( arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_AOISpace_updateAvatar::exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		std::size_t exceptionId;
		_ar.readSize( exceptionId );
	
		if( this->exceptionFilter( exceptionId, _ar ) == true )
		{
			return;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<Response_AOISpace_finalizePtr>::BindResponse( const TBindResponse & _response, const TBindException & _exception )
		: m_response(_response)
		, m_exception(_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_AOISpace_finalizePtr>::response( const Proxy_AOITilePtr & _arg0 )
	{
		m_response( _arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_AOISpace_finalizePtr>::throw_exception( const Axe::Exception & _ex )
	{
		m_exception( _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_AOISpace_finalize::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		Proxy_AOITilePtr arg0; _ar >> arg0;
		this->response( arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_AOISpace_finalize::exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		std::size_t exceptionId;
		_ar.readSize( exceptionId );
	
		if( this->exceptionFilter( exceptionId, _ar ) == true )
		{
			return;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	Proxy_AOISpace::Proxy_AOISpace( std::size_t _id, const Axe::ProxyHostProviderPtr & _hostProvider )
		: Axe::Proxy(_id, _hostProvider)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_AOISpace::insertAvatar_async( const Response_AOISpace_insertAvatarPtr & _response, __compiler__type__error _userPrx, const AOIAvatarDesc & _desc )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 1, _response );
		ar << _userPrx;
		ar << _desc;
	
		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_AOISpace::removeAvatar_async( const Response_AOISpace_removeAvatarPtr & _response, int _userId )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 2, _response );
		ar << _userId;
	
		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_AOISpace::moveAvatar_async( const Response_AOISpace_moveAvatarPtr & _response, int _userId, const AOIAvatarMoveDesc & _moveDesc )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 3, _response );
		ar << _userId;
		ar << _moveDesc;
	
		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_AOISpace::updateAvatar_async( const Response_AOISpace_updateAvatarPtr & _response, int _userId )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 4, _response );
		ar << _userId;
	
		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_AOISpace::finalize_async( const Response_AOISpace_finalizePtr & _response )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 5, _response );
	
		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & _ar, const Proxy_AOISpacePtr & _value )
	{
		_value->write( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	void s_Servant_AOISpaceFactory_callMethod_createSpace( Servant_AOISpaceFactory * _servant, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_AOISpaceFactory_createSpacePtr bellhop = new Bellhop_AOISpaceFactory_createSpace( _requestId, _session, _servant );
	
	
		_servant->createSpace_async( bellhop );
	}
	//////////////////////////////////////////////////////////////////////////
	void s_Servant_AOISpaceFactory_callMethod_destroySpace( Servant_AOISpaceFactory * _servant, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_AOISpaceFactory_destroySpacePtr bellhop = new Bellhop_AOISpaceFactory_destroySpace( _requestId, _session, _servant );
	
		Proxy_AOISpacePtr arg0; _archive >> arg0;
	
		_servant->destroySpace_async( bellhop, arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_AOISpaceFactory_callMethod)( Servant_AOISpaceFactory * _servant, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session );
	//////////////////////////////////////////////////////////////////////////
	static TServant_AOISpaceFactory_callMethod s_Servant_AOISpaceFactory_callMethods[] =
	{
		0
		, &s_Servant_AOISpaceFactory_callMethod_createSpace
		, &s_Servant_AOISpaceFactory_callMethod_destroySpace
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_AOISpaceFactory::callMethod( std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		(*s_Servant_AOISpaceFactory_callMethods[ _methodId ])( this, _methodId, _requestId, _archive, _session );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_AOISpaceFactory_writeException_createSpace( Servant_AOISpaceFactory * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		Axe::writeExceptionFilter( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_AOISpaceFactory_writeException_destroySpace( Servant_AOISpaceFactory * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		Axe::writeExceptionFilter( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_AOISpaceFactory_writeException)( Servant_AOISpaceFactory * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
	//////////////////////////////////////////////////////////////////////////
	static TServant_AOISpaceFactory_writeException s_Servant_AOISpaceFactory_writeExceptions[] =
	{
		0
		, &s_Servant_AOISpaceFactory_writeException_createSpace
		, &s_Servant_AOISpaceFactory_writeException_destroySpace
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_AOISpaceFactory::responseException( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & aw = _session->beginException( _requestId );
	
		this->writeExceptions_( _methodId, aw, _ex );
	
		_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant_AOISpaceFactory::writeExceptions_( std::size_t _methodId, Axe::ArchiveInvocation & _aw, const Axe::Exception & _ex )
	{
		(*s_Servant_AOISpaceFactory_writeExceptions[ _methodId ])( this, _methodId, _aw, _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_AOISpaceFactory_createSpace::Bellhop_AOISpaceFactory_createSpace( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_AOISpaceFactoryPtr & _servant )
		: Axe::Bellhop(_requestId, _session)
		, m_servant(_servant)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_AOISpaceFactory_createSpace::response( const Proxy_AOISpacePtr & _arg0 )
	{
		Axe::ArchiveInvocation & ar = m_session->beginResponse( m_requestId );
		ar << _arg0;
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_AOISpaceFactory_createSpace::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = m_session->beginException( m_requestId );
		s_Servant_AOISpaceFactory_writeException_createSpace( AxeUtil::nativePtr(m_servant), 3, ar, _ex );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_AOISpaceFactory_destroySpace::Bellhop_AOISpaceFactory_destroySpace( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_AOISpaceFactoryPtr & _servant )
		: Axe::Bellhop(_requestId, _session)
		, m_servant(_servant)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_AOISpaceFactory_destroySpace::response()
	{
		Axe::ArchiveInvocation & ar = m_session->beginResponse( m_requestId );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_AOISpaceFactory_destroySpace::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = m_session->beginException( m_requestId );
		s_Servant_AOISpaceFactory_writeException_destroySpace( AxeUtil::nativePtr(m_servant), 4, ar, _ex );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<Response_AOISpaceFactory_createSpacePtr>::BindResponse( const TBindResponse & _response, const TBindException & _exception )
		: m_response(_response)
		, m_exception(_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_AOISpaceFactory_createSpacePtr>::response( const Proxy_AOISpacePtr & _arg0 )
	{
		m_response( _arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_AOISpaceFactory_createSpacePtr>::throw_exception( const Axe::Exception & _ex )
	{
		m_exception( _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_AOISpaceFactory_createSpace::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		Proxy_AOISpacePtr arg0; _ar >> arg0;
		this->response( arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_AOISpaceFactory_createSpace::exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		std::size_t exceptionId;
		_ar.readSize( exceptionId );
	
		if( this->exceptionFilter( exceptionId, _ar ) == true )
		{
			return;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<Response_AOISpaceFactory_destroySpacePtr>::BindResponse( const TBindResponse & _response, const TBindException & _exception )
		: m_response(_response)
		, m_exception(_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_AOISpaceFactory_destroySpacePtr>::response()
	{
		m_response();
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_AOISpaceFactory_destroySpacePtr>::throw_exception( const Axe::Exception & _ex )
	{
		m_exception( _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_AOISpaceFactory_destroySpace::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		this->response();
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_AOISpaceFactory_destroySpace::exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		std::size_t exceptionId;
		_ar.readSize( exceptionId );
	
		if( this->exceptionFilter( exceptionId, _ar ) == true )
		{
			return;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	Proxy_AOISpaceFactory::Proxy_AOISpaceFactory( std::size_t _id, const Axe::ProxyHostProviderPtr & _hostProvider )
		: Axe::Proxy(_id, _hostProvider)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_AOISpaceFactory::createSpace_async( const Response_AOISpaceFactory_createSpacePtr & _response )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 1, _response );
	
		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_AOISpaceFactory::destroySpace_async( const Response_AOISpaceFactory_destroySpacePtr & _response, const Proxy_AOISpacePtr & spaceProxy )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 2, _response );
		ar << spaceProxy;
	
		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & _ar, const Proxy_AOISpaceFactoryPtr & _value )
	{
		_value->write( _ar );
	}
}
