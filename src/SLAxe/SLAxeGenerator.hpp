#	pragma once

#	include "SLAxeDeclaration.hpp"

namespace Axe
{
	class SLAxeParser;

	class SLAxeGenerator
	{
	public:
		SLAxeGenerator( SLAxeParser * _parser );

	protected:
		void typegen( const Declaration::Namespace & ns );

	public:
		void generateHeader();
		void generateImplement( const std::string & _fileName );

	public:
		std::stringstream & getStream();

	protected:
		void generateHeaderNamespace( const Declaration::Namespace & _namespace );
		void generateHeaderStruct( const Declaration::Struct & _struct );
		void generateHeaderTypedef( const Declaration::Typedef & _typedef );

		void generateHeaderClass( const Declaration::Class & _class );
		void generateHeaderBellhop( const Declaration::Class & _class );
		void generateHeaderServant( const Declaration::Class & _class );
		void generateHeaderResponse( const Declaration::Class & _class );
		void generateHeaderProxy( const Declaration::Class & _class );

	protected:
		void generateImplementNamespace( const Declaration::Namespace & _namespace );
		void generateImplementStruct( const Declaration::Struct & _struct );
		void generateImplementClass( const Declaration::Class & _class );
		
		void generateImplementBellhop( const Declaration::Class & _class );
		void generateImplementServant( const Declaration::Class & _class );
		void generateImplementResponse( const Declaration::Class & _class );
		void generateImplementProxy( const Declaration::Class & _class );

	protected:
		std::string writeBellhopeName( const std::string & _class, const std::string & _method );
		std::string writeServantName( const std::string & _class );
		std::string writeEnumMethodName( const std::string & _class, const std::string & _method );
		std::string writeResponseName( const std::string & _class, const std::string & _method );
		std::string writeProxyName( const std::string & _class );

	protected:
		std::string writeArgumentType( const std::string & _type );
		std::string writeMemberType( const std::string & _type );
		std::string writeTemplates( const std::string & _type );

	protected:
		void writeLine();


	protected:
		void increfTabs();
		void decrefTabs();

	protected:
		std::stringstream & write();

	protected:
		SLAxeParser * m_parser;
		std::stringstream m_stream;

		unsigned int m_tabs;
		bool m_lockTabs;

		typedef std::set<std::string> TSetTypes;
		TSetTypes m_podTypes;
		TSetTypes m_specTypes;
		TSetTypes m_typedefTypes;
		TSetTypes m_structTypes;
		TSetTypes m_classTypes;
		TSetTypes m_templatesTypes;
	};
}