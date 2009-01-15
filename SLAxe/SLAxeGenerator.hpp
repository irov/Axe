#	pragma once

#	include "SLAxeDeclaration.hpp"

namespace Axe
{
	class SLAxeParser;

	class SLAxeGenerator
	{
	public:
		SLAxeGenerator( SLAxeParser * _parser );

	public:
		void run();

	public:
		std::strstream & getStream();

	protected:
		void generateHeader();
		void generateStruct( const Declaration::Struct & _struct );
		void generateTypedef( const Declaration::Typedef & _typedef );

		void generateClass( const Declaration::Class & _class );
		void generateBellhop( const Declaration::Class & _class );

	protected:
		std::string writeArgumentType( const std::string & _type );
		std::string writeMemberType( const std::string & _type );
		std::string writeTemplates( const std::string & _type );

	protected:
		SLAxeParser * m_parser;
		std::strstream m_stream;

		typedef std::set<std::string> TSetTypes;
		TSetTypes m_podTypes;
		TSetTypes m_specTypes;
		TSetTypes m_structTypes;
		TSetTypes m_classTypes;
		TSetTypes m_templatesTypes;
	};
}