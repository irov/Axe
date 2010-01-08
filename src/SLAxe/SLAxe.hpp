#	pragma once

#	include <string>
#	include <map>

namespace Axe
{
	class SLAxeGenerator;
	class SLAxeParser;
	class SLAxeGrammar;

	class SLAxe
	{
	public:
		SLAxe();

	public:
		bool make( const std::string & _protocol, const std::string & _path, const std::string & _name ); 

	protected:
		SLAxeParser * parse_( const std::string & _protocol );
		void generate_( SLAxeParser * _parser, const std::string & _path, const std::string & _name );

	protected:
		SLAxeGrammar * m_grammar;

		typedef std::map<std::string, SLAxeParser *> TMapParsers;
		TMapParsers m_parsers;
	};
}