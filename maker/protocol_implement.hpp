#	pragma once

#	include <boost/preprocessor/seq.hpp>
#	include <boost/preprocessor/cat.hpp>
#	include <boost/preprocessor/punctuation/comma_if.hpp>
#	include <boost/preprocessor/seq/for_each_i.hpp>


#	define IMPLEMENT_BELLHOP_ARGS(r, data, i , elem) BOOST_PP_COMMA_IF(i) elem BOOST_PP_CAT(a,i)
#	define IMPLEMENT_BELLHOP_WRITE(r, data, i, elem) ssocket->write( BOOST_PP_CAT(a,i) );\n

#	define IMPLEMENT_BELLHOP(r, data, elem)																				\
	BOOST_PP_CAT(bellhop_, BOOST_PP_SEQ_ELEM(0, elem) )::BOOST_PP_CAT(bellhop_, BOOST_PP_SEQ_ELEM(0, elem) )			\
	( std::size_t _requestId, adapter_session * _session )\n																\
	: bellhop(_requestId, _session){}\n																				\
	void BOOST_PP_CAT(bellhop_, BOOST_PP_SEQ_ELEM(0, elem) )														\
		::response( BOOST_PP_SEQ_FOR_EACH_I( IMPLEMENT_BELLHOP_ARGS, _, BOOST_PP_SEQ_ELEM(2, elem) ) )\n		\
	{\n																													\
	stream_write * ssocket = m_session->begin_response( m_requestId );\n																								\
	BOOST_PP_SEQ_FOR_EACH_I( IMPLEMENT_BELLHOP_WRITE, _, BOOST_PP_SEQ_ELEM(2, elem) )								\
	m_session->procces();\n																						\
	}\n\n

#	define IMPLEMENT_METHOD_ENUM(r, data, i, elem) const int BOOST_PP_CAT( enum_method_, BOOST_PP_SEQ_ELEM(0, elem) ) = i;\n

#	define IMPLEMENT_CASE_SELECT(r, data, i, elem)								\
	elem * BOOST_PP_CAT(a,i);\n													\
	stream->select( &BOOST_PP_CAT(a,i) );\n

#	define IMPLEMENT_CASE_CALL(r, data, i, elem) , *BOOST_PP_CAT(a,i)

#	define IMPLEMENT_CASE_METHOD(r, data, elem)																			\
		case BOOST_PP_CAT( enum_method_, BOOST_PP_SEQ_ELEM(0, elem) ):\n																\
			{\n																											\
			BOOST_PP_CAT(bellhop_, BOOST_PP_SEQ_ELEM(0, elem) ) * bellhop\n												\
				= new BOOST_PP_CAT(bellhop_, BOOST_PP_SEQ_ELEM(0, elem) )( _requestId, _session );\n					\
			BOOST_PP_SEQ_FOR_EACH_I( IMPLEMENT_CASE_SELECT, _, BOOST_PP_SEQ_ELEM(1, elem) )\n						\
			this->BOOST_PP_SEQ_ELEM(0, elem)( bellhop BOOST_PP_SEQ_FOR_EACH_I( IMPLEMENT_CASE_CALL, _, BOOST_PP_SEQ_ELEM(1, elem) ) );\n	\
			}break;\n

#	define IMPLEMENT_RESPONSE_SELECT(r, data, i, elem)											\
	elem * BOOST_PP_CAT(a,i);\n																	\
	_stream->select( &BOOST_PP_CAT(a,i) );\n													

#	define IMPLEMENT_RESPONSE_CALL( r, data, i, elem) BOOST_PP_COMMA_IF(i) *BOOST_PP_CAT(a,i)

#	define IMPLEMENT_RESPONSE(r, data, elem)																		\
	void BOOST_PP_CAT(response_, BOOST_PP_SEQ_ELEM(0, elem) )														\
	::response_call( stream_read * _stream )\n										\
	{\n																												\
	BOOST_PP_SEQ_FOR_EACH_I( IMPLEMENT_RESPONSE_SELECT, _, BOOST_PP_SEQ_ELEM(2, elem) )\n							\
	this->response( BOOST_PP_SEQ_FOR_EACH_I( IMPLEMENT_RESPONSE_CALL, _, BOOST_PP_SEQ_ELEM(2, elem) ) );\n		\
	}\n\n

#	define IMPLEMENT_PROXY_METHOD_ARGS(r, data, i, elem) BOOST_PP_COMMA_IF(i) elem BOOST_PP_CAT(a,i)
#	define IMPLEMENT_PROXY_METHOD_WRITE(r, data, i, elem) stream->write( BOOST_PP_CAT(a,i) );\n

#	define IMPLEMENT_PROXY_METHOD(r, data, elem)															\
	void proxy:: BOOST_PP_CAT(BOOST_PP_SEQ_ELEM(0, elem),_async)(											\
	BOOST_PP_SEQ_FOR_EACH_I( IMPLEMENT_PROXY_METHOD_ARGS, _, BOOST_PP_SEQ_ELEM(1, elem) )				\
	, BOOST_PP_CAT(response_,BOOST_PP_SEQ_ELEM(0, elem)) * _response )\n										\
	{\n																										\
	stream_write * stream = this->begin_message( BOOST_PP_CAT( enum_method_, BOOST_PP_SEQ_ELEM(0, elem) ), _response );\n					\
	BOOST_PP_SEQ_FOR_EACH_I( IMPLEMENT_PROXY_METHOD_WRITE, _, BOOST_PP_SEQ_ELEM(1, elem) )				\
	this->procces();\n																					\
	}\n\n

#	define IMPLEMENT_PROTOCOL( name, methods )																\
	namespace BOOST_PP_CAT(protocol_, name){\n																	\
	BOOST_PP_SEQ_FOR_EACH( IMPLEMENT_BELLHOP, _, methods )\n													\
	BOOST_PP_SEQ_FOR_EACH_I( IMPLEMENT_METHOD_ENUM, _, methods )\n											\
	void servant::call_method( std::size_t _methodId, std::size_t _requestId, adapter_session * _session )\n		\
	{\n																										\
	stream_read * stream = _session->get_streamIn();\n														\
	switch( _methodId ){\n																						\
	BOOST_PP_SEQ_FOR_EACH( IMPLEMENT_CASE_METHOD, _, methods )\n										\
		}\n																									\
	}\n																										\
	BOOST_PP_SEQ_FOR_EACH( IMPLEMENT_RESPONSE, _, methods )\n													\
	proxy::proxy( std::size_t _id, connection * _cn )\n												\
	: proxy_base( _id, _cn){}\n																		\
	BOOST_PP_SEQ_FOR_EACH( IMPLEMENT_PROXY_METHOD, _, methods )\n												\
}\n
