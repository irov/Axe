#	pragma once

#	include <boost/preprocessor/seq.hpp>
#	include <boost/preprocessor/cat.hpp>
#	include <boost/preprocessor/punctuation/comma_if.hpp>
#	include <boost/preprocessor/seq/for_each_i.hpp>

#	define DECLARE_BELLHOP_ARGS(r, data, i, elem) BOOST_PP_COMMA_IF(i) elem

#	define DECLARE_BELLHOP(r, data, elem)																			\
class BOOST_PP_CAT(bellhop_, BOOST_PP_SEQ_ELEM(0, elem) )\n															\
	: public bellhop\n																								\
{\n																													\
public:\n																												\
	BOOST_PP_CAT(bellhop_, BOOST_PP_SEQ_ELEM(0, elem) )( std::size_t _requestId, adapter_session * _session );\n			\
public:\n																												\
	void response( BOOST_PP_SEQ_FOR_EACH_I( DECLARE_BELLHOP_ARGS, _, BOOST_PP_SEQ_ELEM(2, elem) ) );\n				\
};\n\n

#	define DECLARE_SERVANT_METHOD_ARGS( r, data, i, elem ) , elem BOOST_PP_CAT(a,i)

#	define DECLARE_SERVANT_METHOD( r, data, elem )													\
	virtual void BOOST_PP_SEQ_ELEM(0, elem)(														\
	BOOST_PP_CAT(bellhop_, BOOST_PP_SEQ_ELEM(0, elem)) * _bellhop									\
	BOOST_PP_SEQ_FOR_EACH_I( DECLARE_SERVANT_METHOD_ARGS, _, BOOST_PP_SEQ_ELEM(1, elem)  )			\
	) = 0;\n


#	define DECLARE_RESPONSE_ARGS(r, data, i, elem) BOOST_PP_COMMA_IF(i) elem

#	define DECLARE_RESPONSE(r, data, elem)																			\
class BOOST_PP_CAT(response_, BOOST_PP_SEQ_ELEM(0, elem) )\n															\
	: public response_base\n																							\
{\n																													\
public:\n																												\
	virtual void response( BOOST_PP_SEQ_FOR_EACH_I( DECLARE_RESPONSE_ARGS, _, BOOST_PP_SEQ_ELEM(2, elem) ) ) = 0;\n	\
private:\n																											\
	void response_call( stream_read * _stream ) override;\n								\
};\n\n

#	define DECLARE_PROXY_METHOD_ARGS( r, data, i, elem ) elem BOOST_PP_CAT(a,i) ,

#	define DECLARE_PROXY_METHOD( r, data, elem )												\
	void BOOST_PP_CAT(BOOST_PP_SEQ_ELEM(0, elem),_async)(										\
	BOOST_PP_SEQ_FOR_EACH_I( DECLARE_PROXY_METHOD_ARGS, _, BOOST_PP_SEQ_ELEM(1, elem)  )		\
	BOOST_PP_CAT(response_,BOOST_PP_SEQ_ELEM(0, elem)) * _response								\
	);\n



#	define DECLARE_PROTOCOL( name, methods )												\
	namespace BOOST_PP_CAT(protocol_, name){\n												\
	BOOST_PP_SEQ_FOR_EACH( DECLARE_BELLHOP, _, methods )\n									\
class servant : public servant_base\n															\
{\n																							\
public:\n																						\
	BOOST_PP_SEQ_FOR_EACH( DECLARE_SERVANT_METHOD, _, methods )\n								\
private:\n																					\
	void call_method( std::size_t _methodId														\
	, std::size_t _requestId																\
	, adapter_session * _session ) override;\n												\
};\n\n																							\
	BOOST_PP_SEQ_FOR_EACH( DECLARE_RESPONSE, _, methods )\n									\
class proxy: public proxy_base\n 																\
{\n																							\
public:\n																						\
	proxy( std::size_t _id, connection * _cn );\n										\
	BOOST_PP_SEQ_FOR_EACH( DECLARE_PROXY_METHOD, _, methods )\n								\
};\n																							\
}\n






