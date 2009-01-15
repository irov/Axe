#	include "pch.hpp"

#	include "SLAxeParser.hpp"

namespace Axe
{
	using namespace Axe::Declaration;

	//////////////////////////////////////////////////////////////////////////
	SLAxeParser::SLAxeParser()
	{
	}
	//////////////////////////////////////////////////////////////////////////
	const TVectorClasses & SLAxeParser::getClasses() const
	{
		return m_classes;
	}
	//////////////////////////////////////////////////////////////////////////
	const Declaration::TVectorStructs & SLAxeParser::getStructs() const
	{
		return m_structs;
	}
	//////////////////////////////////////////////////////////////////////////
	const Declaration::TVectorTypedefs & SLAxeParser::getTypedefs() const
	{
		return m_typedefs;
	}
	//////////////////////////////////////////////////////////////////////////
	const Declaration::TVectorOrder & SLAxeParser::getOrder() const
	{
		return m_order;
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeParser::set_class_name( char const* str, char const* end )
	{
		m_class.name = std::string( str, end );
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeParser::add_class( char const* str, char const* end )
	{				
		m_classes.push_back( m_class );
		
		m_order.push_back( DECL_CLASS );

		m_class = Class();
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeParser::set_struct_name( char const* str, char const* end )
	{
		m_struct.name = std::string( str, end );
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeParser::add_struct( char const* str, char const* end )
	{				
		m_structs.push_back( m_struct );

		m_order.push_back( DECL_STRUCT );

		m_struct = Struct();
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeParser::set_parent_name( char const* str, char const* end)
	{
		Parent parent;
		parent.name = std::string( str, end );
		parent.inheritance = m_inheritance;

		m_class.parents.push_back( parent );
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeParser::set_inheritance_type( char const* str, char const* end )
	{
		m_inheritance = std::string( str, end );
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeParser::add_member( char const* str, char const* end )
	{
		Member member;

		member.name = std::string( str, end );
		member.type = m_type;

		if( m_class.name.empty() == false )
		{
			m_class.members.push_back( member );
		}
		else if( m_struct.name.empty() == false )
		{
			m_struct.members.push_back( member );
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeParser::set_type_name( char const* str, char const* end )
	{
		m_type.name = std::string(str, end);
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeParser::add_typedef( char const* str, char const* end )
	{
		m_typedefs.push_back( m_typedef );

		m_order.push_back( DECL_TYPEDEF );
		
		m_typedef = Typedef();
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeParser::set_typedef_name( char const* str, char const* end )
	{
		m_typedef.name = std::string( str, end );
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeParser::set_typedef_type( char const* str, char const* end )
	{
		m_typedef.type = std::string( str, end );
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeParser::add_type_to_template_list( char const* str, char const* end )
	{
		m_typedef.templates.push_back( m_type );
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeParser::add_method( char const* str, char const* end )
	{
		m_class.methods.push_back( m_method );

		m_method = Method();
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeParser::set_method_name( char const* str, char const* end )
	{
		m_method.name = std::string(str, end);
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeParser::add_in_argument( char const* str, char const* end )
	{
		Argument arg;
		arg.name = std::string(str, end);
		arg.type = m_type;

		m_method.inArguments.push_back( arg );
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeParser::add_default_out_argument( char const* str, char const* end )
	{
		Argument arg;
		arg.name = std::string("__result__");
		arg.type = m_type;

		m_method.outArguments.push_back( arg );
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeParser::add_out_argument( char const* str, char const* end )
	{
		Argument arg;
		arg.name = std::string(str, end);
		arg.type = m_type;

		m_method.outArguments.push_back( arg );
	}
}