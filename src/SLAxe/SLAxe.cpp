#	include "pch.hpp"

#	include "SLAxe.hpp"
#	include "SLAxeGrammar.hpp"
#	include "SLAxeGenerator.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	SLAxe::SLAxe()
	{
		m_grammar = new SLAxeGrammar;
	}
	//////////////////////////////////////////////////////////////////////////
	SLAxeParser * SLAxe::parse_( const std::string & _protocol )
	{
		TMapParsers::iterator it_found = m_parsers.find( _protocol );

		if( it_found != m_parsers.end() )
		{
			return it_found->second;
		}

		FILE * file_in = fopen( _protocol.c_str(), "rb" );

		if( file_in == 0 )
		{
			return 0;
		}

		fseek( file_in, 0L, SEEK_END );
		long size = ftell( file_in );
		rewind( file_in );

		if( size == 0 )
		{
			return 0;
		}

		char * buff = new char[ size ];

		fread( buff, size, 1, file_in );
		fclose( file_in );

		SLAxeParser * parser = m_grammar->parser( buff, size );

		if( parser == 0 )
		{
			return 0;
		}

		m_parsers.insert( std::make_pair(_protocol, parser) );

		const Declaration::TVectorIncludes & includes = parser->getIncludes();

		for( Declaration::TVectorIncludes::const_iterator
			it = includes.begin(),
			it_end = includes.end();
		it != it_end;
		++it )
		{
			if( parse_( it->path + ".axe" ) == 0 )
			{
				return 0;
			}
		}

		return parser;
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxe::generate_( SLAxeParser * _parser, const std::string & _path, const std::string & _name )
	{
		SLAxeGenerator generator( _parser, m_parsers );

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
	}
	//////////////////////////////////////////////////////////////////////////
	bool SLAxe::make( const std::string & _protocol, const std::string & _path, const std::string & _name )
	{
		SLAxeParser * parser = parse_( _protocol );

		if( parser == 0 )
		{
			return false;
		}

		generate_( parser, _path, _name );

		//printf("%s\n", str );

		return true;
	}
}