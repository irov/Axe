#	include "pch.hpp"

#	include "SLAxeGrammar.hpp"

namespace Axe
{
	SLAxeGrammar::SLAxeGrammar()
	{
		m_parser = new SLAxeParser();
	}

	SLAxeParser * SLAxeGrammar::getParser() const
	{	
		return m_parser;
	}
}