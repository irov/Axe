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

	public:
		void set_class_name( char const* str, char const* end );
		void add_class( char const* str, char const* end );
		void set_struct_name( char const* str, char const* end );
		void add_struct( char const* str, char const* end );

		void begin_namespace( char const* str, char const* end );
		void end_namespace( char const* str, char const* end );
		
		void set_parent_name( char const* str, char const* end);
		void set_inheritance_type( char const* str, char const* end );
		void add_member( char const* str, char const* end );
		void set_type_name( char const* str, char const* end );

		void add_typedef( char const* str, char const* end );
		void set_typedef_name( char const* str, char const* end );
		void set_typedef_type( char const* str, char const* end );

		void add_type_to_template_list( char const* str, char const* end );
		void add_method( char const* str, char const* end );
		void set_method_name( char const* str, char const* end );
		void add_in_argument( char const* str, char const* end );
		void add_default_out_argument( char const* str, char const* end );
		void add_out_argument( char const* str, char const* end );

	protected:
		Declaration::TVectorNamespaces m_namespaces;

		std::string m_inheritance;

		Declaration::Class m_class;
		Declaration::Struct m_struct;
		Declaration::Method m_method;
		Declaration::Typedef m_typedef;
		Declaration::Type m_type;
	};
}