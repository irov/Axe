#	pragma once

#	include "SLAxeParser.hpp"

namespace Axe
{
	class SLAxeGrammar
		: public boost::spirit::grammar<SLAxeGrammar>
	{
	public:
		SLAxeGrammar();

	public:
		SLAxeParser * parser( char * _buff, std::size_t _size );

	public:
		template<class T>
		class definition
		{
		public:
			definition( SLAxeGrammar const& _self )
			{
				SLAxeParser * parser = _self.getParser();

				root
					= +definition_frame
					;

				definition_frame
					= simport | sexception | sclass | sstruct | typedefs | namespaces
					;

				simport
					= "import"
					>> name[ boost::bind( &SLAxeParser::add_include_path, parser, _1, _2 ) ]
					;

				sstruct
					= "struct" >> name[ boost::bind( &SLAxeParser::set_struct_name, parser, _1, _2 ) ] >> !parents >> struct_body[ boost::bind( &SLAxeParser::add_struct, parser, _1, _2 ) ]
				;

				sclass
					= "class" >> name[ boost::bind( &SLAxeParser::set_class_name, parser, _1, _2 ) ] >> !parents >> class_body[ boost::bind( &SLAxeParser::add_class, parser, _1, _2 ) ]
				;

				sexception
					= "exception" >> name[ boost::bind( &SLAxeParser::set_exception_name, parser, _1, _2 ) ] >> !parents >> struct_body[ boost::bind( &SLAxeParser::add_exception, parser, _1, _2 ) ]
				;

				typedefs
					= (	"typedef" 
					>> name[ boost::bind( &SLAxeParser::set_typedef_type, parser, _1, _2 ) ] 
					>> !typedefs_template_type_list 
					>> name[ boost::bind( &SLAxeParser::set_typedef_name, parser, _1, _2 ) ] >> ';')
					[ boost::bind( &SLAxeParser::add_typedef, parser, _1, _2 ) ]
				;

				typedefs_template_type_list
					=
					boost::spirit::ch_p('<') 
					>> type[ boost::bind( &SLAxeParser::add_type_to_template_list, parser, _1, _2 ) ] 
					>> *(',' >> +type[ boost::bind( &SLAxeParser::add_type_to_template_list, parser, _1, _2 ) ])
					>> boost::spirit::ch_p('>')
					;

				namespaces
					= ("namespace" >> name[ boost::bind( &SLAxeParser::begin_namespace, parser, _1, _2 ) ] >> 
					'{' >> *definition_frame >> '}')
					[ boost::bind( &SLAxeParser::end_namespace, parser, _1, _2 ) ]
				;

				parents
					= ':' >> parent >> *(',' >> +parent)
					;

				parent
					= !inheritance_type >> name[ boost::bind( &SLAxeParser::set_parent_name, parser, _1, _2 ) ]
				;

				struct_body
					= '{' >> *member >> '}' >> ';'
					;

				class_body
					= '{' >> *(member | method) >> '}' >> ';'
					;

				member
					= ( type[ boost::bind( &SLAxeParser::set_member_type, parser, _1, _2 ) ] >> name[ boost::bind( &SLAxeParser::set_member_name, parser, _1, _2 ) ] >> ';' )
					[ boost::bind( &SLAxeParser::add_member, parser, _1, _2 ) ]
				;

				method
					= (	type[ boost::bind( &SLAxeParser::add_default_out_argument, parser, _1, _2 ) ] >> 
					name[ boost::bind( &SLAxeParser::set_method_name, parser, _1, _2 ) ] >> 
					'(' >> !method_argument_list >> ')'	>> !throws_body >> ';' )[ boost::bind( &SLAxeParser::add_method, parser, _1, _2 ) ]
				;

				throws_body
					= "throws" >> throws_name >> *(',' >> +throws_name)
					;

				throws_name
					= name[ boost::bind( &SLAxeParser::add_exception_to_method, parser, _1, _2 ) ] 
				;

				method_argument_list
					= method_argument >> *(',' >> +method_argument)
					;

				method_argument
					= *(boost::spirit::str_p("out")[ boost::bind( &SLAxeParser::set_argument_out, parser, _1, _2 ) ]) >> type >> name[ boost::bind( &SLAxeParser::add_argument, parser, _1, _2 ) ];

				inheritance_type
					= (boost::spirit::str_p("public") | boost::spirit::str_p("private") | boost::spirit::str_p("protected"))
					[ boost::bind( &SLAxeParser::set_inheritance_type, parser, _1, _2 ) ]
				;


				complex_type
					= template_type | type
					;

				type
					= boost::spirit::lexeme_d[name >> *("::" >> name)][ boost::bind( &SLAxeParser::set_type_name, parser, _1, _2 ) ]
				;

				name
					= boost::spirit::lexeme_d[(boost::spirit::alpha_p | '_') >> *(boost::spirit::alnum_p | '_')]
				;
			}

			boost::spirit::rule<T> const& start() const 
			{
				return root;
			}

		protected:
			boost::spirit::rule<T> root, definition_frame, 
				simport, sstruct, sclass, sexception, typedefs, namespaces,
				parents, parent, struct_body, class_body, include_helper, include_body,
				member, method, method_argument_list, method_argument, throws_body, throws_name,

				typedefs_template_type_list, complex_type, type, template_type,
				inheritance_type, name;
		};

		public:
			SLAxeParser * getParser() const;

		protected:
			SLAxeParser * m_parser;
	};
}