#	include "pch.hpp"
#	include "protocol_session_manager.hpp"
#	include "dispatch/bellhop.hpp"
#	include "dispatch/response_base.hpp"
#	include "dispatch/servant_base.hpp"
#	include "dispatch/proxy_base.hpp"
#	include "dispatch/connection.hpp"
#	include "dispatch/adapter_session.hpp"
#	include "dispatch/stream.hpp"



namespace protocol_session_manager{
 bellhop_create::bellhop_create ( std::size_t _requestId, adapter_session * _session )
 : bellhop(_requestId, _session){}
 void bellhop_create ::response( std::size_t a0 )
 {
 stream_write * ssocket = m_session->begin_response( m_requestId );
 ssocket->write( a0 );
 m_session->procces();
 }

 
 const int enum_method_create = 0;
 
 void servant::call_method( std::size_t _methodId, std::size_t _requestId, adapter_session * _session )
 {
 stream_read * stream = _session->get_streamIn();
 switch( _methodId ){
 case enum_method_create:
 {
 bellhop_create * bellhop
 = new bellhop_create( _requestId, _session );
 std::string * a0;
 stream->select( &a0 );
 std::string * a1;
 stream->select( &a1 );
 
 this->create ( bellhop , *a0 , *a1 );
 }break;
 
 }
 }
 void response_create ::response_call( stream_read * _stream )
 {
 std::size_t * a0;
 _stream->select( &a0 );
 
 this->response( *a0 );
 }

 
 proxy::proxy( std::size_t _id, connection * _cn )
 : proxy_base( _id, _cn){}
 void proxy:: create_async( std::string a0 , std::string a1 , response_create * _response )
 {
 stream_write * stream = this->begin_message( enum_method_create, _response );
 stream->write( a0 );
 stream->write( a1 );
 this->procces();
 }

 
 }
