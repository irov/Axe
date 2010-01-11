#	include "pch.hpp"

#	include "PathFinderSystem.hpp"

#	include <Axe/ArchiveInvocation.hpp>
#	include <Axe/ArchiveDispatcher.hpp>
#	include <Axe/ProxyHostProvider.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & ar, const PathFinderAvatarDesc & _value )
	{
		ar << _value.pos;
		ar << _value.speed;
		ar << _value.radius;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator >> ( Axe::ArchiveDispatcher & ar, PathFinderAvatarDesc & _value )
	{
		ar >> _value.pos;
		ar >> _value.speed;
		ar >> _value.radius;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & ar, const PathFinderCluster & _value )
	{
		ar << _value.type;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator >> ( Axe::ArchiveDispatcher & ar, PathFinderCluster & _value )
	{
		ar >> _value.type;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & ar, const PathFinderSpaceDesc & _value )
	{
		ar << _value.width;
		ar << _value.height;
		ar << _value.m_clusters;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator >> ( Axe::ArchiveDispatcher & ar, PathFinderSpaceDesc & _value )
	{
		ar >> _value.width;
		ar >> _value.height;
		ar >> _value.m_clusters;
	}
	//////////////////////////////////////////////////////////////////////////
	void s_Servant_PathFinderSpace_callMethod_addAvatar( Servant_PathFinderSpace * _servant, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_PathFinderSpace_addAvatarPtr bellhop = new Bellhop_PathFinderSpace_addAvatar( _requestId, _session, _servant );
	
		PathFinderAvatarDesc arg0; _archive >> arg0;
	
		_servant->addAvatar_async( bellhop, arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void s_Servant_PathFinderSpace_callMethod_moveTo( Servant_PathFinderSpace * _servant, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_PathFinderSpace_moveToPtr bellhop = new Bellhop_PathFinderSpace_moveTo( _requestId, _session, _servant );
	
		AvatarId arg0; _archive >> arg0;
		AxeProtocol::Position arg1; _archive >> arg1;
	
		_servant->moveTo_async( bellhop, arg0, arg1 );
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_PathFinderSpace_callMethod)( Servant_PathFinderSpace * _servant, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session );
	//////////////////////////////////////////////////////////////////////////
	static TServant_PathFinderSpace_callMethod s_Servant_PathFinderSpace_callMethods[] =
	{
		0
		, &s_Servant_PathFinderSpace_callMethod_addAvatar
		, &s_Servant_PathFinderSpace_callMethod_moveTo
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_PathFinderSpace::callMethod( std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		(*s_Servant_PathFinderSpace_callMethods[ _methodId ])( this, _methodId, _requestId, _archive, _session );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_PathFinderSpace_writeException_addAvatar( Servant_PathFinderSpace * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		Axe::writeExceptionFilter( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_PathFinderSpace_writeException_moveTo( Servant_PathFinderSpace * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		Axe::writeExceptionFilter( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_PathFinderSpace_writeException)( Servant_PathFinderSpace * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
	//////////////////////////////////////////////////////////////////////////
	static TServant_PathFinderSpace_writeException s_Servant_PathFinderSpace_writeExceptions[] =
	{
		0
		, &s_Servant_PathFinderSpace_writeException_addAvatar
		, &s_Servant_PathFinderSpace_writeException_moveTo
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_PathFinderSpace::responseException( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & aw = _session->beginException( _requestId );
	
		this->writeExceptions_( _methodId, aw, _ex );
	
		_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant_PathFinderSpace::writeExceptions_( std::size_t _methodId, Axe::ArchiveInvocation & _aw, const Axe::Exception & _ex )
	{
		(*s_Servant_PathFinderSpace_writeExceptions[ _methodId ])( this, _methodId, _aw, _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant_PathFinderSpace::_restore( ArchiveDispatcher & _ar )
	{
		_ar >> m_desc;
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant_PathFinderSpace::_evict( ArchiveInvocation & _aw )
	{
		_aw << m_desc;
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_PathFinderSpace_addAvatar::Bellhop_PathFinderSpace_addAvatar( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_PathFinderSpacePtr & _servant )
		: Axe::Bellhop(_requestId, _session)
		, m_servant(_servant)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_PathFinderSpace_addAvatar::response( __compiler__type__error _arg0 )
	{
		Axe::ArchiveInvocation & ar = m_session->beginResponse( m_requestId );
		ar << _arg0;
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_PathFinderSpace_addAvatar::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = m_session->beginException( m_requestId );
		s_Servant_PathFinderSpace_writeException_addAvatar( AxeUtil::nativePtr(m_servant), 3, ar, _ex );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_PathFinderSpace_moveTo::Bellhop_PathFinderSpace_moveTo( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_PathFinderSpacePtr & _servant )
		: Axe::Bellhop(_requestId, _session)
		, m_servant(_servant)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_PathFinderSpace_moveTo::response()
	{
		Axe::ArchiveInvocation & ar = m_session->beginResponse( m_requestId );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_PathFinderSpace_moveTo::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = m_session->beginException( m_requestId );
		s_Servant_PathFinderSpace_writeException_moveTo( AxeUtil::nativePtr(m_servant), 4, ar, _ex );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<Response_PathFinderSpace_addAvatarPtr>::BindResponse( const TBindResponse & _response, const TBindException & _exception )
		: m_response(_response)
		, m_exception(_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_PathFinderSpace_addAvatarPtr>::response( __compiler__type__error _arg0 )
	{
		m_response( _arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_PathFinderSpace_addAvatarPtr>::throw_exception( const Axe::Exception & _ex )
	{
		m_exception( _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_PathFinderSpace_addAvatar::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		AvatarId arg0; _ar >> arg0;
		this->response( arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_PathFinderSpace_addAvatar::exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		std::size_t exceptionId;
		_ar.readSize( exceptionId );
	
		if( this->exceptionFilter( exceptionId, _ar ) == true )
		{
			return;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<Response_PathFinderSpace_moveToPtr>::BindResponse( const TBindResponse & _response, const TBindException & _exception )
		: m_response(_response)
		, m_exception(_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_PathFinderSpace_moveToPtr>::response()
	{
		m_response();
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_PathFinderSpace_moveToPtr>::throw_exception( const Axe::Exception & _ex )
	{
		m_exception( _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_PathFinderSpace_moveTo::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		this->response();
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_PathFinderSpace_moveTo::exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		std::size_t exceptionId;
		_ar.readSize( exceptionId );
	
		if( this->exceptionFilter( exceptionId, _ar ) == true )
		{
			return;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	Proxy_PathFinderSpace::Proxy_PathFinderSpace( std::size_t _id, const Axe::ProxyHostProviderPtr & _hostProvider )
		: Axe::Proxy(_id, _hostProvider)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_PathFinderSpace::addAvatar_async( const Response_PathFinderSpace_addAvatarPtr & _response, const PathFinderAvatarDesc & _desc )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 1, _response );
		ar << _desc;
	
		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_PathFinderSpace::moveTo_async( const Response_PathFinderSpace_moveToPtr & _response, __compiler__type__error _id, const AxeProtocol::Position & _pos )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 2, _response );
		ar << _id;
		ar << _pos;
	
		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & _ar, const Proxy_PathFinderSpacePtr & _value )
	{
		_value->write( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	void s_Servant_PathFinderManager_callMethod_createSpace( Servant_PathFinderManager * _servant, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		Bellhop_PathFinderManager_createSpacePtr bellhop = new Bellhop_PathFinderManager_createSpace( _requestId, _session, _servant );
	
		PathFinderSpaceDesc arg0; _archive >> arg0;
	
		_servant->createSpace_async( bellhop, arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_PathFinderManager_callMethod)( Servant_PathFinderManager * _servant, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session );
	//////////////////////////////////////////////////////////////////////////
	static TServant_PathFinderManager_callMethod s_Servant_PathFinderManager_callMethods[] =
	{
		0
		, &s_Servant_PathFinderManager_callMethod_createSpace
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_PathFinderManager::callMethod( std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )
	{
		(*s_Servant_PathFinderManager_callMethods[ _methodId ])( this, _methodId, _requestId, _archive, _session );
	}
	//////////////////////////////////////////////////////////////////////////
	static void s_Servant_PathFinderManager_writeException_createSpace( Servant_PathFinderManager * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )
	{
		Axe::writeExceptionFilter( _ar );
	}
	//////////////////////////////////////////////////////////////////////////
	typedef void (*TServant_PathFinderManager_writeException)( Servant_PathFinderManager * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );
	//////////////////////////////////////////////////////////////////////////
	static TServant_PathFinderManager_writeException s_Servant_PathFinderManager_writeExceptions[] =
	{
		0
		, &s_Servant_PathFinderManager_writeException_createSpace
	};
	//////////////////////////////////////////////////////////////////////////
	void Servant_PathFinderManager::responseException( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & aw = _session->beginException( _requestId );
	
		this->writeExceptions_( _methodId, aw, _ex );
	
		_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant_PathFinderManager::writeExceptions_( std::size_t _methodId, Axe::ArchiveInvocation & _aw, const Axe::Exception & _ex )
	{
		(*s_Servant_PathFinderManager_writeExceptions[ _methodId ])( this, _methodId, _aw, _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	Bellhop_PathFinderManager_createSpace::Bellhop_PathFinderManager_createSpace( std::size_t _requestId, const Axe::SessionPtr & _session, const Servant_PathFinderManagerPtr & _servant )
		: Axe::Bellhop(_requestId, _session)
		, m_servant(_servant)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_PathFinderManager_createSpace::response( const Proxy_PathFinderSpacePtr & _arg0 )
	{
		Axe::ArchiveInvocation & ar = m_session->beginResponse( m_requestId );
		ar << _arg0;
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	void Bellhop_PathFinderManager_createSpace::throw_exception( const Axe::Exception & _ex )
	{
		Axe::ArchiveInvocation & ar = m_session->beginException( m_requestId );
		s_Servant_PathFinderManager_writeException_createSpace( AxeUtil::nativePtr(m_servant), 3, ar, _ex );
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	BindResponse<Response_PathFinderManager_createSpacePtr>::BindResponse( const TBindResponse & _response, const TBindException & _exception )
		: m_response(_response)
		, m_exception(_exception)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_PathFinderManager_createSpacePtr>::response( const Proxy_PathFinderSpacePtr & _arg0 )
	{
		m_response( _arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void BindResponse<Response_PathFinderManager_createSpacePtr>::throw_exception( const Axe::Exception & _ex )
	{
		m_exception( _ex );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_PathFinderManager_createSpace::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		Proxy_PathFinderSpacePtr arg0; _ar >> arg0;
		this->response( arg0 );
	}
	//////////////////////////////////////////////////////////////////////////
	void Response_PathFinderManager_createSpace::exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )
	{
		std::size_t exceptionId;
		_ar.readSize( exceptionId );
	
		if( this->exceptionFilter( exceptionId, _ar ) == true )
		{
			return;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	Proxy_PathFinderManager::Proxy_PathFinderManager( std::size_t _id, const Axe::ProxyHostProviderPtr & _hostProvider )
		: Axe::Proxy(_id, _hostProvider)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Proxy_PathFinderManager::createSpace_async( const Response_PathFinderManager_createSpacePtr & _response, const PathFinderSpaceDesc & _desc )
	{
		Axe::ArchiveInvocation & ar = this->beginMessage( 1, _response );
		ar << _desc;
	
		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & _ar, const Proxy_PathFinderManagerPtr & _value )
	{
		_value->write( _ar );
	}
}
