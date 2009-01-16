#	include "pch.hpp"

#	include "SLAxe.hpp"
#	include "SLAxeGrammar.hpp"
#	include "SLAxeGenerator.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	SLAxe::SLAxe()
	{
		m_grammar = new SLAxeGrammar();
	}
	//////////////////////////////////////////////////////////////////////////
	bool SLAxe::generate( const char * _protocol, const char * _code )
	{
		FILE * file_in = fopen( _protocol, "rb" );

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

		boost::spirit::parse_info<> info = boost::spirit::parse( 
			buff, buff + size, 
			*m_grammar, boost::spirit::space_p 
			);

		if( info.full == false )
		{
			return false;
		}

		SLAxeParser * parser = m_grammar->getParser();

		SLAxeGenerator generator( parser );

		generator.run();

		std::strstream & stream = generator.getStream();

		char * str = stream.str();

		std::streamsize stream_size = stream.pcount();

		FILE * file_out = fopen( _code, "wb" );

		fwrite( str, stream_size, 1, file_out );
		fclose( file_out );

		//printf("%s\n", str );

		return true;
	}
}