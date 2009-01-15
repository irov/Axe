#	pragma once
#	include "dispatch/bellhop.hpp"
#	include "dispatch/response_base.hpp"
#	include "dispatch/servant_base.hpp"
#	include "dispatch/proxy_base.hpp"



namespace protocol_grid{
 class bellhop_add_adapter
 : public bellhop
 {
 public:
 bellhop_add_adapter( std::size_t _requestId, adapter_session * _session );
 public:
 void response( std::size_t );
 };

 class bellhop_get_servant_info
 : public bellhop
 {
 public:
 bellhop_get_servant_info( std::size_t _requestId, adapter_session * _session );
 public:
 void response( std::string , unsigned short );
 };

 class bellhop_get_adapter_id
 : public bellhop
 {
 public:
 bellhop_get_adapter_id( std::size_t _requestId, adapter_session * _session );
 public:
 void response( std::string , unsigned short );
 };

 
 class servant : public servant_base
 {
 public:
 virtual void add_adapter ( bellhop_add_adapter * _bellhop , std::string a0 , std::string a1 , unsigned short a2 ) = 0;
 virtual void get_servant_info ( bellhop_get_servant_info * _bellhop , std::string a0 ) = 0;
 virtual void get_adapter_id ( bellhop_get_adapter_id * _bellhop , size_t a0 ) = 0;
 
 private:
 void call_method( std::size_t _methodId , std::size_t _requestId , adapter_session * _session ) override;
 };

 class response_add_adapter
 : public response_base
 {
 public:
 virtual void response( std::size_t ) = 0;
 private:
 void response_call( stream_read * _stream ) override;
 };

 class response_get_servant_info
 : public response_base
 {
 public:
 virtual void response( std::string , unsigned short ) = 0;
 private:
 void response_call( stream_read * _stream ) override;
 };

 class response_get_adapter_id
 : public response_base
 {
 public:
 virtual void response( std::string , unsigned short ) = 0;
 private:
 void response_call( stream_read * _stream ) override;
 };

 
 class proxy: public proxy_base
 {
 public:
 proxy( std::size_t _id, connection * _cn );
 void add_adapter_async( std::string a0 , std::string a1 , unsigned short a2 , response_add_adapter * _response );
 void get_servant_info_async( std::string a0 , response_get_servant_info * _response );
 void get_adapter_id_async( size_t a0 , response_get_adapter_id * _response );
 
 };
 }

