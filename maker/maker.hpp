#	pragma once

#	define PROTOCOL_PATH "../protocols/"

#	define WRITE_F( text, f ) {const char buff[] = text ;fwrite(buff, sizeof(buff)-1, 1, f);}

#	define MAKE_PROTOCOL( name, methods )\
		{\
		FILE * f = fopen( PROTOCOL_PATH BOOST_PP_STRINGIZE( BOOST_PP_CAT( BOOST_PP_CAT( protocol_, name ), .hpp) ), "wt" );\
		WRITE_F( "#	pragma once\n", f );\
		WRITE_F( "#	include \"dispatch/bellhop.hpp\"\n", f );\
		WRITE_F( "#	include \"dispatch/response_base.hpp\"\n", f );\
		WRITE_F( "#	include \"dispatch/servant_base.hpp\"\n", f );\
		WRITE_F( "#	include \"dispatch/proxy_base.hpp\"\n", f );\
		WRITE_F( "\n\n\n", f );\
		WRITE_F( BOOST_PP_STRINGIZE( DECLARE_PROTOCOL( name, methods ) ), f );\
		WRITE_F( "\n", f );\
		fclose(f);\
		}\
		{\
		FILE * f = fopen( PROTOCOL_PATH BOOST_PP_STRINGIZE( BOOST_PP_CAT( BOOST_PP_CAT( protocol_, name ), .cpp) ), "wt" );\
		WRITE_F( "#	include \"pch.hpp\"\n", f );\
		WRITE_F( "#	include \"", f);\
		WRITE_F( BOOST_PP_STRINGIZE( BOOST_PP_CAT( BOOST_PP_CAT( protocol_, name ), .hpp) ), f );\
		WRITE_F( "\"\n", f );\
		WRITE_F( "#	include \"dispatch/bellhop.hpp\"\n", f );\
		WRITE_F( "#	include \"dispatch/response_base.hpp\"\n", f );\
		WRITE_F( "#	include \"dispatch/servant_base.hpp\"\n", f );\
		WRITE_F( "#	include \"dispatch/proxy_base.hpp\"\n", f );\
		WRITE_F( "#	include \"dispatch/connection.hpp\"\n", f );\
		WRITE_F( "#	include \"dispatch/adapter_session.hpp\"\n", f );\
		WRITE_F( "#	include \"dispatch/stream.hpp\"\n", f );\
		WRITE_F( "\n\n\n", f );\
		WRITE_F( BOOST_PP_STRINGIZE( IMPLEMENT_PROTOCOL( name, methods ) ), f );\
		printf( BOOST_PP_STRINGIZE( ( IMPLEMENT_PROTOCOL( name, methods ) ) ) );\
		fclose(f);\
		}

#	define CARBON_METHOD( name, args, retr ) ((name)(args)(retr))
#	define CARBON_METHOD_VOID( name, args ) ((name)(args)(BOOST_PP_SEQ_NIL))
