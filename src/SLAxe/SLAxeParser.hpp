#	pragma once

#	include "SLAxeDeclaration.hpp"

namespace Axe
{
	class SLAxeParser
	{
	public:
		SLAxeParser();

	public:
		const Declaration::Namespace & getNamespace() const;
		const Declaration::TVectorIncludes & getIncludes() const;

	public:
		void set_class_name( char const* str, char const* end );
		void add_class( char const* str, char const* end );
		void set_struct_name( char const* str, char const* end );
		void add_struct( char const* str, char const* end );
		void set_exception_name( char const* str, char const* end );
		void add_exception( char const* str, char const* end );

		void add_include_path( char const* str, char const* end );

		void begin_namespace( char const* str, char const* end );
		void end_namespace( char const* str, char const* end );
		
		void set_parent_name( char const* str, char const* end);
		void set_inheritance_type( char const* str, char const* end );
		void set_member_type( char const* str, char const* end );
		void set_member_name( char const* str, char const* end );
		void add_member( char const* str, char const* end );


		void set_type_name( char const* str, char const* end );

		void add_typedef( char const* str, char const* end );
		void set_typedef_name( char const* str, char const* end );
		void set_typedef_type( char const* str, char const* end );

		void add_type_to_template_list( char const* str, char const* end );
		void add_method( char const* str, char const* end );
		void set_method_name( char const* str, char const* end );

		void set_argument_out( char const* str, char const* end );
		void add_argument( char const* str, char const* end );
		void add_default_out_argument( char const* str, char const* end );
		void add_exception_to_method( char const* str, char const* end );


	protected:
		Declaration::TVectorIncludes m_includes;
		Declaration::TVectorNamespaces m_namespaces;

		std::string m_inheritance;

		bool m_outArgument;
		Declaration::Class m_class;
		Declaration::Struct m_struct;
		Declaration::Exception m_exception;
		Declaration::Method m_method;
		Declaration::Member m_member;
		Declaration::Typedef m_typedef;
		Declaration::Type m_type;
	};
}