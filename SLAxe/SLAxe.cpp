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
		FILE * file = fopen( _protocol, "rb" );

		if( file == 0 )
		{
			return false;
		}

		fseek( file, 0L, SEEK_END );
		long size = ftell( file );
		rewind( file );

		if( size == 0 )
		{
			return true;
		}

		char * buff = new char[ size ];

		fread( buff, size, 1, file );
		fclose( file );

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
		printf("%s\n", str );

		return true;
	}
}