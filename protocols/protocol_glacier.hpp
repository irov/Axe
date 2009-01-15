#	pragma once
#	include "dispatch/bellhop.hpp"
#	include "dispatch/response_base.hpp"
#	include "dispatch/servant_base.hpp"
#	include "dispatch/proxy_base.hpp"



namespace protocol_glacier{
 class bellhop_create
 : public bellhop
 {
 public:
 bellhop_create( std::size_t _requestId, adapter_session * _session );
 public:
 void response( std::size_t );
 };

 
 class servant : public servant_base
 {
 public:
 virtual void create ( bellhop_create * _bellhop , std::string a0 , std::string a1 ) = 0;
 
 private:
 void call_method( std::size_t _methodId , std::size_t _requestId , adapter_session * _session ) override;
 };

 class response_create
 : public response_base
 {
 public:
 virtual void response( std::size_t ) = 0;
 private:
 void response_call( connection * _cn ) override;
 };

 
 class proxy: public proxy_base
 {
 public:
 proxy( std::size_t _id, connection * _cn );
 void create_async( std::string a0 , std::string a1 , response_create * _response );
 
 };
 }

