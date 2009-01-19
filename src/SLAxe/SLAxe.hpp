#	pragma once

#	include "SLAxeDeclaration.hpp"

namespace Axe
{
	class SLAxeGrammar;

	class SLAxe
	{
	public:
		SLAxe();

	public:
		bool generate( const char * _protocol, const char * _path, const char * _name ); 

	protected:
		SLAxeGrammar * m_grammar;
	};
}