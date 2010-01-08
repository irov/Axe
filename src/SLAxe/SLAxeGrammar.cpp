#	include "pch.hpp"

#	include "SLAxeGrammar.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	SLAxeGrammar::SLAxeGrammar()
	{
		m_parser = new SLAxeParser;
	}
	//////////////////////////////////////////////////////////////////////////
	SLAxeParser * SLAxeGrammar::parser( char * _buff, std::size_t _size )
	{
		boost::spirit::parse_info<> info = boost::spirit::parse( 
			_buff, _buff + _size, 
			*this, boost::spirit::space_p 
			);

		if( info.full == false )
		{
			return 0;
		}

		SLAxeParser * newParser = new SLAxeParser(*m_parser);

		*m_parser = SLAxeParser();

		return newParser;
	}
	//////////////////////////////////////////////////////////////////////////
	SLAxeParser * SLAxeGrammar::getParser() const
	{
		return m_parser;
	}
}