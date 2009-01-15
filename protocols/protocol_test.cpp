#	include "pch.hpp"
#	include "protocol_test.hpp"
#	include "dispatch/bellhop.hpp"
#	include "dispatch/response_base.hpp"
#	include "dispatch/servant_base.hpp"
#	include "dispatch/proxy_base.hpp"
#	include "dispatch/connection.hpp"
#	include "dispatch/adapter_session.hpp"
#	include "dispatch/stream.hpp"



namespace protocol_test{
 bellhop_foo::bellhop_foo ( std::size_t _requestId, adapter_session * _session )
 : bellhop(_requestId, _session){}
 void bellhop_foo ::response( )
 {
 stream_write * ssocket = m_session->begin_response( m_requestId );
 m_session->procces();
 }

 bellhop_bar::bellhop_bar ( std::size_t _requestId, adapter_session * _session )
 : bellhop(_requestId, _session){}
 void bellhop_bar ::response( float a0 )
 {
 stream_write * ssocket = m_session->begin_response( m_requestId );
 ssocket->write( a0 );
 m_session->procces();
 }

 bellhop_moo::bellhop_moo ( std::size_t _requestId, adapter_session * _session )
 : bellhop(_requestId, _session){}
 void bellhop_moo ::response( float a0 , float a1 )
 {
 stream_write * ssocket = m_session->begin_response( m_requestId );
 ssocket->write( a0 );
 ssocket->write( a1 );
 m_session->procces();
 }

 bellhop_too::bellhop_too ( std::size_t _requestId, adapter_session * _session )
 : bellhop(_requestId, _session){}
 void bellhop_too ::response( )
 {
 stream_write * ssocket = m_session->begin_response( m_requestId );
 m_session->procces();
 }

 
 const int enum_method_foo = 0;
 const int enum_method_bar = 1;
 const int enum_method_moo = 2;
 const int enum_method_too = 3;
 
 void servant::call_method( std::size_t _methodId, std::size_t _requestId, adapter_session * _session )
 {
 stream_read * stream = _session->get_streamIn();
 switch( _methodId ){
 case enum_method_foo:
 {
 bellhop_foo * bellhop
 = new bellhop_foo( _requestId, _session );
 int * a0;
 stream->select( &a0 );
 float * a1;
 stream->select( &a1 );
 
 this->foo ( bellhop , *a0 , *a1 );
 }break;
 case enum_method_bar:
 {
 bellhop_bar * bellhop
 = new bellhop_bar( _requestId, _session );
 int * a0;
 stream->select( &a0 );
 
 this->bar ( bellhop , *a0 );
 }break;
 case enum_method_moo:
 {
 bellhop_moo * bellhop
 = new bellhop_moo( _requestId, _session );
 int * a0;
 stream->select( &a0 );
 float * a1;
 stream->select( &a1 );
 float * a2;
 stream->select( &a2 );
 
 this->moo ( bellhop , *a0 , *a1 , *a2 );
 }break;
 case enum_method_too:
 {
 bellhop_too * bellhop
 = new bellhop_too( _requestId, _session );
 float * a0;
 stream->select( &a0 );
 
 this->too ( bellhop , *a0 );
 }break;
 
 }
 }
 void response_foo ::response_call( stream_read * _stream )
 {
 
 this->response( );
 }

 void response_bar ::response_call( stream_read * _stream )
 {
 float * a0;
 _stream->select( &a0 );
 
 this->response( *a0 );
 }

 void response_moo ::response_call( stream_read * _stream )
 {
 float * a0;
 _stream->select( &a0 );
 float * a1;
 _stream->select( &a1 );
 
 this->response( *a0 , *a1 );
 }

 void response_too ::response_call( stream_read * _stream )
 {
 
 this->response( );
 }

 
 proxy::proxy( std::size_t _id, connection * _cn )
 : proxy_base( _id, _cn){}
 void proxy:: foo_async( int a0 , float a1 , response_foo * _response )
 {
 stream_write * stream = this->begin_message( enum_method_foo, _response );
 stream->write( a0 );
 stream->write( a1 );
 this->procces();
 }

 void proxy:: bar_async( int a0 , response_bar * _response )
 {
 stream_write * stream = this->begin_message( enum_method_bar, _response );
 stream->write( a0 );
 this->procces();
 }

 void proxy:: moo_async( int a0 , float a1 , float a2 , response_moo * _response )
 {
 stream_write * stream = this->begin_message( enum_method_moo, _response );
 stream->write( a0 );
 stream->write( a1 );
 stream->write( a2 );
 this->procces();
 }

 void proxy:: too_async( float a0 , response_too * _response )
 {
 stream_write * stream = this->begin_message( enum_method_too, _response );
 stream->write( a0 );
 this->procces();
 }

 
 }
