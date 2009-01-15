#	pragma once
#	include "dispatch/bellhop.hpp"
#	include "dispatch/response_base.hpp"
#	include "dispatch/servant_base.hpp"
#	include "dispatch/proxy_base.hpp"



namespace protocol_test{
 class bellhop_foo
 : public bellhop
 {
 public:
 bellhop_foo( std::size_t _requestId, adapter_session * _session );
 public:
 void response( );
 };

 class bellhop_bar
 : public bellhop
 {
 public:
 bellhop_bar( std::size_t _requestId, adapter_session * _session );
 public:
 void response( float );
 };

 class bellhop_moo
 : public bellhop
 {
 public:
 bellhop_moo( std::size_t _requestId, adapter_session * _session );
 public:
 void response( float , float );
 };

 class bellhop_too
 : public bellhop
 {
 public:
 bellhop_too( std::size_t _requestId, adapter_session * _session );
 public:
 void response( );
 };

 
 class servant : public servant_base
 {
 public:
 virtual void foo ( bellhop_foo * _bellhop , int a0 , float a1 ) = 0;
 virtual void bar ( bellhop_bar * _bellhop , int a0 ) = 0;
 virtual void moo ( bellhop_moo * _bellhop , int a0 , float a1 , float a2 ) = 0;
 virtual void too ( bellhop_too * _bellhop , float a0 ) = 0;
 
 private:
 void call_method( std::size_t _methodId , std::size_t _requestId , adapter_session * _session ) override;
 };

 class response_foo
 : public response_base
 {
 public:
 virtual void response( ) = 0;
 private:
 void response_call( stream_read * _stream ) override;
 };

 class response_bar
 : public response_base
 {
 public:
 virtual void response( float ) = 0;
 private:
 void response_call( stream_read * _stream ) override;
 };

 class response_moo
 : public response_base
 {
 public:
 virtual void response( float , float ) = 0;
 private:
 void response_call( stream_read * _stream ) override;
 };

 class response_too
 : public response_base
 {
 public:
 virtual void response( ) = 0;
 private:
 void response_call( stream_read * _stream ) override;
 };

 
 class proxy: public proxy_base
 {
 public:
 proxy( std::size_t _id, connection * _cn );
 void foo_async( int a0 , float a1 , response_foo * _response );
 void bar_async( int a0 , response_bar * _response );
 void moo_async( int a0 , float a1 , float a2 , response_moo * _response );
 void too_async( float a0 , response_too * _response );
 
 };
 }

