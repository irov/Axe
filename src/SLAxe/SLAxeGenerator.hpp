#	pragma once

#	include "SLAxeDeclaration.hpp"

namespace Axe
{
	class SLAxeParser;

	typedef std::map<std::string, SLAxeParser *> TMapParsers;

	class SLAxeGenerator
	{
	public:
		SLAxeGenerator( SLAxeParser * _parser, const TMapParsers & _parsers );

	protected:
		void typegen( const Declaration::Namespace & ns );

	public:
		void generateHeader( const std::string & _path, const std::string & _fileName );
		void generateImplement( const std::string & _fileName );

	public:
		std::stringstream & getStream();

	protected:
		const Declaration::Class * findClass( const std::string & _name ) const;
		const Declaration::Class * findClass_ns( const Declaration::Namespace & _namespace, const std::string & _name ) const;

	protected:
		typedef std::vector<const Declaration::Class *> TVectorBaseClasses;
		void getBasesClass( const Declaration::Class & _class, TVectorBaseClasses & _out );

	protected:
		void generateHeaderIncludes( const Declaration::TVectorIncludes & _includes, const std::string & _path );
		void generateHeaderNamespace( const Declaration::Namespace & _namespace );
		void generateHeaderStruct( const Declaration::Struct & _struct );
		void generateHeaderTypedef( const Declaration::Typedef & _typedef );
		void generateHeaderException( const Declaration::Exception & _class );

		void generateHeaderClass( const Declaration::Class & _class );
		void generateHeaderBellhop( const Declaration::Class & _class );
		void generateHeaderServant( const Declaration::Class & _class );
		void generateHeaderResponse( const Declaration::Class & _class );
		void generateHeaderProxy( const Declaration::Class & _class );

	protected:
		void generateImplementNamespace( const Declaration::Namespace & _namespace );
		void generateImplementStruct( const Declaration::Namespace & _namespace, const Declaration::Struct & _struct );
		void generateImplementClass( const Declaration::Namespace & _namespace, const Declaration::Class & _class );
		void generateImplementException( const Declaration::Namespace & _namespace, const Declaration::Exception & _ex );
		
		void generateImplementBellhop( const Declaration::Namespace & _namespace, const Declaration::Class & _class );
		void generateImplementServant( const Declaration::Namespace & _namespace, const Declaration::Class & _class );
		void generateImplementResponse( const Declaration::Namespace & _namespace, const Declaration::Class & _class );
		void generateImplementProxy( const Declaration::Namespace & _namespace, const Declaration::Class & _class );


	protected:
		void writeTypedefHandle( const std::string & _type );

	protected:
		std::string writeBellhopName( const std::string & _class, const std::string & _method );
		std::string writeServantName( const std::string & _class );
		std::string writeResponseName( const std::string & _class, const std::string & _method );
		std::string writeProxyName( const std::string & _class );

	protected:
		std::string writeArgumentType( const std::string & _type );
		std::string writeMemberType( const std::string & _type );
		std::string writeTemplates( const std::string & _type );

	protected:
		void writeSelectType( const std::string & _ar, const std::string & _type, std::size_t _enum );
		void writeReadType( const std::string & _ar, const std::string & _type, const std::string & _name );
		void writeLine();

	protected:
		void increfTabs();
		void decrefTabs();

	protected:
		std::stringstream & write();

	protected:
		SLAxeParser * m_parser;
		TMapParsers m_parsers;

		std::stringstream m_stream;

		unsigned int m_tabs;
		bool m_lockTabs;

		typedef std::set<std::string> TSetTypes;
		TSetTypes m_podTypes;
		TSetTypes m_specTypes;
		TSetTypes m_templatesTypes;

		TSetTypes m_typedefTypes;
		TSetTypes m_structTypes;
		TSetTypes m_classTypes;
	};
}