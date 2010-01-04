#	include "pch.hpp"

#	include "SLAxe.hpp"
#	include "SLAxeGrammar.hpp"
#	include "SLAxeGenerator.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	bool SLAxe::generate( const std::string & _protocol, const std::string & _path, const std::string & _name )
	{
		FILE * file_in = fopen( _protocol.c_str(), "rb" );

		if( file_in == 0 )
		{
			return false;
		}

		fseek( file_in, 0L, SEEK_END );
		long size = ftell( file_in );
		rewind( file_in );

		if( size == 0 )
		{
			return true;
		}

		char * buff = new char[ size ];

		fread( buff, size, 1, file_in );
		fclose( file_in );

		SLAxeGrammar * grammar = new SLAxeGrammar();

		boost::spirit::parse_info<> info = boost::spirit::parse( 
			buff, buff + size, 
			*grammar, boost::spirit::space_p 
			);

		if( info.full == false )
		{
			return false;
		}

		SLAxeParser * parser = grammar->getParser();

		SLAxeGenerator generator( parser );

		{
			generator.generateHeader( _path, _name );

			std::stringstream & stream = generator.getStream();

			std::string code_out = _path;
			code_out += _name;
			code_out += ".hpp";

			FILE * file_out = fopen( code_out.c_str(), "wb" );

			std::string stream_buff = stream.str();

			fwrite( stream_buff.c_str(), stream_buff.size(), 1, file_out );
			fclose( file_out );
		}

		{
			generator.generateImplement( _name );

			std::stringstream & stream = generator.getStream();

			std::string code_out = _path;
			code_out += _name;
			code_out += ".cpp";

			FILE * file_out = fopen( code_out.c_str(), "wb" );

			std::string stream_buff = stream.str();

			fwrite( stream_buff.c_str(), stream_buff.size(), 1, file_out );
			fclose( file_out );		
		}

		delete grammar;

		//printf("%s\n", str );

		return true;
	}
}