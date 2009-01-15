#	include "pch.hpp"
#	include "protocol_grid.hpp"
#	include "dispatch/bellhop.hpp"
#	include "dispatch/response_base.hpp"
#	include "dispatch/servant_base.hpp"
#	include "dispatch/proxy_base.hpp"
#	include "dispatch/connection.hpp"
#	include "dispatch/adapter_session.hpp"
#	include "dispatch/stream.hpp"



namespace protocol_grid{
 bellhop_add_adapter::bellhop_add_adapter ( std::size_t _requestId, adapter_session * _session )
 : bellhop(_requestId, _session){}
 void bellhop_add_adapter ::response( std::size_t a0 )
 {
 stream_write * ssocket = m_session->begin_response( m_requestId );
 ssocket->write( a0 );
 m_session->procces();
 }

 bellhop_get_servant_info::bellhop_get_servant_info ( std::size_t _requestId, adapter_session * _session )
 : bellhop(_requestId, _session){}
 void bellhop_get_servant_info ::response( std::string a0 , unsigned short a1 )
 {
 stream_write * ssocket = m_session->begin_response( m_requestId );
 ssocket->write( a0 );
 ssocket->write( a1 );
 m_session->procces();
 }

 bellhop_get_adapter_id::bellhop_get_adapter_id ( std::size_t _requestId, adapter_session * _session )
 : bellhop(_requestId, _session){}
 void bellhop_get_adapter_id ::response( std::string a0 , unsigned short a1 )
 {
 stream_write * ssocket = m_session->begin_response( m_requestId );
 ssocket->write( a0 );
 ssocket->write( a1 );
 m_session->procces();
 }

 
 const int enum_method_add_adapter = 0;
 const int enum_method_get_servant_info = 1;
 const int enum_method_get_adapter_id = 2;
 
 void servant::call_method( std::size_t _methodId, std::size_t _requestId, adapter_session * _session )
 {
 stream_read * stream = _session->get_streamIn();
 switch( _methodId ){
 case enum_method_add_adapter:
 {
 bellhop_add_adapter * bellhop
 = new bellhop_add_adapter( _requestId, _session );
 std::string * a0;
 stream->select( &a0 );
 std::string * a1;
 stream->select( &a1 );
 unsigned short * a2;
 stream->select( &a2 );
 
 this->add_adapter ( bellhop , *a0 , *a1 , *a2 );
 }break;
 case enum_method_get_servant_info:
 {
 bellhop_get_servant_info * bellhop
 = new bellhop_get_servant_info( _requestId, _session );
 std::string * a0;
 stream->select( &a0 );
 
 this->get_servant_info ( bellhop , *a0 );
 }break;
 case enum_method_get_adapter_id:
 {
 bellhop_get_adapter_id * bellhop
 = new bellhop_get_adapter_id( _requestId, _session );
 size_t * a0;
 stream->select( &a0 );
 
 this->get_adapter_id ( bellhop , *a0 );
 }break;
 
 }
 }
 void response_add_adapter ::response_call( stream_read * _stream )
 {
 std::size_t * a0;
 _stream->select( &a0 );
 
 this->response( *a0 );
 }

 void response_get_servant_info ::response_call( stream_read * _stream )
 {
 std::string * a0;
 _stream->select( &a0 );
 unsigned short * a1;
 _stream->select( &a1 );
 
 this->response( *a0 , *a1 );
 }

 void response_get_adapter_id ::response_call( stream_read * _stream )
 {
 std::string * a0;
 _stream->select( &a0 );
 unsigned short * a1;
 _stream->select( &a1 );
 
 this->response( *a0 , *a1 );
 }

 
 proxy::proxy( std::size_t _id, connection * _cn )
 : proxy_base( _id, _cn){}
 void proxy:: add_adapter_async( std::string a0 , std::string a1 , unsigned short a2 , response_add_adapter * _response )
 {
 stream_write * stream = this->begin_message( enum_method_add_adapter, _response );
 stream->write( a0 );
 stream->write( a1 );
 stream->write( a2 );
 this->procces();
 }

 void proxy:: get_servant_info_async( std::string a0 , response_get_servant_info * _response )
 {
 stream_write * stream = this->begin_message( enum_method_get_servant_info, _response );
 stream->write( a0 );
 this->procces();
 }

 void proxy:: get_adapter_id_async( size_t a0 , response_get_adapter_id * _response )
 {
 stream_write * stream = this->begin_message( enum_method_get_adapter_id, _response );
 stream->write( a0 );
 this->procces();
 }

 
 }
