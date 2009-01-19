#	include "pch.hpp"

#	include "SLAxeParser.hpp"

namespace Axe
{
	using namespace Axe::Declaration;

	//////////////////////////////////////////////////////////////////////////
	SLAxeParser::SLAxeParser()
	{
		m_namespaces.push_back( Namespace() );
	}
	//////////////////////////////////////////////////////////////////////////
	const Namespace & SLAxeParser::getNamespace() const
	{
		return m_namespaces.back();
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeParser::set_class_name( char const* str, char const* end )
	{
		m_class.name = std::string( str, end );
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeParser::add_class( char const* str, char const* end )
	{	
		Namespace & nm = m_namespaces.back();

		nm.classes.push_back( m_class );
		nm.order.push_back( DECL_CLASS );

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
		Namespace & nm = m_namespaces.back();

		nm.structs.push_back( m_struct );
		nm.order.push_back( DECL_STRUCT );

		m_struct = Struct();
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeParser::begin_namespace( char const* str, char const* end )
	{
		m_namespaces.push_back( Namespace() );

		Namespace & nm = m_namespaces.back();

		nm.name.assign( str, end );
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeParser::end_namespace( char const* str, char const* end )
	{
		Namespace & nm_parent = *(m_namespaces.end() - 2);

		nm_parent.namespaces.push_back( m_namespaces.back() );
		nm_parent.order.push_back( DECL_NAMESPACE );

		m_namespaces.pop_back();
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeParser::set_parent_name( char const* str, char const* end)
	{
		Parent parent;
		parent.name.assign( str, end );
		parent.inheritance = m_inheritance;

		if( m_class.name.empty() == false )
		{
			m_class.parents.push_back( parent );
		}
		else if( m_struct.name.empty() == false )
		{
			m_struct.parents.push_back( parent );
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeParser::set_inheritance_type( char const* str, char const* end )
	{
		m_inheritance.assign( str, end );
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeParser::add_member( char const* str, char const* end )
	{
		Member member;

		member.name.assign( str, end );
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
		m_type.name.assign( str, end );
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeParser::add_typedef( char const* str, char const* end )
	{
		Namespace & nm = m_namespaces.back();

		nm.typedefs.push_back( m_typedef );
		nm.order.push_back( DECL_TYPEDEF );
		
		m_typedef = Typedef();
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeParser::set_typedef_name( char const* str, char const* end )
	{
		m_typedef.name.assign( str, end );
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeParser::set_typedef_type( char const* str, char const* end )
	{
		m_typedef.type.assign( str, end );
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
		m_method.name.assign( str, end );
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeParser::add_in_argument( char const* str, char const* end )
	{
		Argument arg;
		arg.name.assign( str, end );
		arg.type = m_type;

		m_method.inArguments.push_back( arg );
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeParser::add_default_out_argument( char const* str, char const* end )
	{
		if( m_type.name == "void" )
		{
			return;
		}

		Argument arg;
		arg.name = "__result__";
		arg.type = m_type;

		m_method.outArguments.push_back( arg );
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeParser::add_out_argument( char const* str, char const* end )
	{
		Argument arg;
		arg.name.assign( str, end );
		arg.type = m_type;

		m_method.outArguments.push_back( arg );
	}
}