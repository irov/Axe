#	include "pch.hpp"

#	include "SLAxeParser.hpp"
#	include "SLAxeGenerator.hpp"

namespace Axe
{
	using namespace Axe::Declaration;

	//////////////////////////////////////////////////////////////////////////
	SLAxeGenerator::SLAxeGenerator( SLAxeParser * _parser )
		: m_parser(_parser)
	{
		m_podTypes.insert("bool");
		m_podTypes.insert("char");
		m_podTypes.insert("int");
		m_podTypes.insert("float");
		
		m_specTypes.insert("size_t");
		m_specTypes.insert("string");

		m_templatesTypes.insert("map");
		m_templatesTypes.insert("list");
		m_templatesTypes.insert("vector");
		m_templatesTypes.insert("set");

		const TVectorTypedefs & typedefs = m_parser->getTypedefs();

		for( TVectorTypedefs::const_iterator
			it_typedef = typedefs.begin(),
			it_typedef_end = typedefs.end();
		it_typedef != it_typedef_end;
		++it_typedef )
		{
			const Typedef & td = *it_typedef;

			m_typedefTypes.insert( td.name );
		}
		

		const TVectorClasses & classes = m_parser->getClasses();

		for( TVectorClasses::const_iterator
			it_class = classes.begin(),
			it_class_end = classes.end();
		it_class != it_class_end;
		++it_class )
		{
			const Class & cl = *it_class;

			m_classTypes.insert(cl.name);
		}

		const TVectorStructs & structs = m_parser->getStructs();

		for( TVectorStructs::const_iterator
			it_struct = structs.begin(),
			it_struct_end = structs.end();
		it_struct != it_struct_end;
		++it_struct )
		{
			const Struct & st = *it_struct;

			m_structTypes.insert(st.name);
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::run()
	{
		generateHeader();		
	}
	//////////////////////////////////////////////////////////////////////////
	std::strstream & SLAxeGenerator::getStream()
	{
		return m_stream;
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::generateHeader()
	{
		const TVectorOrder & order = m_parser->getOrder();

		const TVectorTypedefs & typedefs = m_parser->getTypedefs();
		const TVectorStructs & structs = m_parser->getStructs();
		const TVectorClasses & classes = m_parser->getClasses();

		TVectorTypedefs::const_iterator it_typedef = typedefs.begin();
		TVectorStructs::const_iterator it_struct = structs.begin();
		TVectorClasses::const_iterator it_class = classes.begin();

		for( TVectorOrder::const_iterator
			it_order = order.begin(),
			it_order_end = order.end();
		it_order != it_order_end;
		++it_order )
		{
			switch( *it_order )
			{
			case DECL_TYPEDEF:
				{
					generateTypedef( *it_typedef );
					++it_typedef;
				}break;
			case DECL_STRUCT:
				{
					generateStruct( *it_struct );
					++it_struct;
				}break;
			case DECL_CLASS:
				{
					generateClass( *it_class );
					++it_class;
				}break;
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::generateStruct( const Struct & _struct )
	{
		m_stream << std::endl;

		const Struct & st = _struct;

		m_stream << "struct " + st.name << std::endl;

		TVectorParents::const_iterator
			it_parent = st.parents.begin(),
			it_parent_end = st.parents.end();

		if( it_parent != it_parent_end )
		{
			m_stream << "	: " << it_parent->inheritance << " " << it_parent->name << std::endl;

			for( ++it_parent ; it_parent != it_parent_end; ++it_parent )
			{
				const Parent & pr = *it_parent;

				m_stream << "	, " << it_parent->inheritance << " " << it_parent->name << std::endl;
			}
		}


		m_stream <<	"{" << std::endl;

		for( TVectorMembers::const_iterator
			it_member = st.members.begin(),
			it_member_end = st.members.end();
		it_member != it_member_end;
		++it_member )
		{
			const Member & mb = *it_member;

			m_stream << "	" << writeMemberType( mb.type.name ) << " " << mb.name << ";" << std::endl;
		}

		m_stream << "};" << std::endl;

		m_stream << std::endl;

		m_stream << "void operator << ( ArchiveWrite & ar, const " << st.name << " & _value )" << std::endl;
		m_stream <<	"{" << std::endl;

		for( TVectorParents::const_iterator
			it_parent = st.parents.begin(),
			it_parent_end = st.parents.end();
		it_parent != it_parent_end;
		++it_parent )
		{
			const Parent & pr = *it_parent;

			m_stream << "	ar << static_cast<const " << pr.name << " &>( _value );" << std::endl;
		}

		for( TVectorMembers::const_iterator
			it_member = st.members.begin(),
			it_member_end = st.members.end();
		it_member != it_member_end;
		++it_member )
		{
			const Member & mb = *it_member;

			m_stream << "	ar << _value." << mb.name << ";" << std::endl;
		}

		m_stream << "}" << std::endl;
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::generateTypedef( const Typedef & _typedef )
	{
		m_stream << std::endl;

		const Typedef & td = _typedef;

		m_stream << "typdef " << writeTemplates( td.type );

		if( td.templates.empty() == false )
		{
			m_stream << "<";

			TVectorTypes::const_iterator 
				it_type = td.templates.begin(),
				it_type_end = td.templates.end();

			m_stream << writeMemberType( it_type->name );

			++it_type;

			for( ; it_type != it_type_end; ++it_type )
			{
				const Type & tp = *it_type;

				m_stream << ", " << writeMemberType( it_type->name );
			}

			m_stream << ">";
		}

		m_stream << " " << td.name << ";" << std::endl;
	}
	void SLAxeGenerator::generateClass( const Declaration::Class & _class )
	{
		generateBellhop( _class );
		generateServant( _class );
		generateResponse( _class );
		generateProxy( _class );
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::generateBellhop( const Class & _class )
	{
		m_stream << std::endl;

		const Class & cl = _class;

		for( TVectorMethods::const_iterator
			it_method = cl.methods.begin(),
			it_method_end = cl.methods.end();
		it_method != it_method_end;
		++it_method )
		{
			const Method & mt = *it_method;

			std::string bellhop_name = "Bellhop_" + cl.name + "_" + mt.name;

			m_stream << "class " << bellhop_name << std::endl;
			m_stream << "	: public Axe::Bellhop" << std::endl;
			m_stream << "{" << std::endl;
			m_stream << "public:" << std::endl;
			m_stream << "	" << bellhop_name << "( std::size_t _requestId, adapter_session * _session );" << std::endl;
			m_stream << "public:" << std::endl;
			m_stream << "	void response(";

			TVectorArguments::const_iterator 
				it_args = mt.outArguments.begin(),
				it_args_end = mt.outArguments.end();

			if( it_args != it_args_end )
			{
				const Argument & ar = *it_args;

				m_stream << " " << writeArgumentType( ar.type.name );

				for( ++it_args; it_args != it_args_end; ++it_args )
				{
					const Argument & ar = *it_args;

					m_stream << ", " << writeArgumentType( ar.type.name ) << " " << ar.name;
				}

				m_stream << " ";
			}


			m_stream << ");" << std::endl;

			m_stream << "};" << std::endl;

			m_stream << "typedef Axe::SharedPtr<" << bellhop_name << "> " << bellhop_name << "Ptr;" << std::endl; 
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::generateServant( const Declaration::Class & _class )
	{
		//class servant : public servant_base
		//{
		//public:
		//	virtual void add_adapter ( bellhop_add_adapter * _bellhop , std::string a0 , std::string a1 , unsigned short a2 ) = 0;
		//	virtual void get_servant_info ( bellhop_get_servant_info * _bellhop , std::string a0 ) = 0;
		//	virtual void get_adapter_id ( bellhop_get_adapter_id * _bellhop , size_t a0 ) = 0;

		//private:
		//	void call_method( std::size_t _methodId , std::size_t _requestId , adapter_session * _session ) override;
		//};

		m_stream << std::endl;

		const Class & cl = _class;

		std::string servant_name = "Servant_" + cl.name;

		m_stream << "class " << servant_name << std::endl;
		m_stream << "	: public Axe::Servant" << std::endl;

		m_stream << "{" << std::endl;
		m_stream << "pulic:" << std::endl;

		for( TVectorMethods::const_iterator
			it_method = cl.methods.begin(),
			it_method_end = cl.methods.end();
		it_method != it_method_end;
		++it_method )
		{
			const Method & mt = *it_method;

			std::string bellhop_name = "Bellhop_" + cl.name + "_" + mt.name + "Ptr";

			m_stream << "	virtual void " << mt.name << "( const " << bellhop_name << " & _cb";

			for( TVectorArguments::const_iterator
				it_args = mt.inArguments.begin(),
				it_args_end = mt.inArguments.end();
			it_args != it_args_end;
			++it_args )
			{
				const Argument & ar = *it_args;

				m_stream << ", " << writeArgumentType( ar.type.name ) << " " << ar.name;
			}

			m_stream << " ) = 0;" << std::endl;
		}

		m_stream << std::endl;

		m_stream << "private:" << std::endl;

		m_stream << "	void call_method( std::size_t _methodId , std::size_t _requestId , adapter_session * _session ) override;" << std::endl;

		m_stream << "};" << std::endl;

		m_stream << "typedef Axe::SharedPtr<" << servant_name << "> " << servant_name << "Ptr;" << std::endl;
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::generateResponse( const Declaration::Class & _class )
	{
		//class response_add_adapter
		//	: public response_base
		//{
		//public:
		//	virtual void response( std::size_t ) = 0;
		//private:
		//	void response_call( stream_read * _stream ) override;
		//};

		m_stream << std::endl;

		const Class & cl = _class;

		for( TVectorMethods::const_iterator
			it_method = cl.methods.begin(),
			it_method_end = cl.methods.end();
		it_method != it_method_end;
		++it_method )
		{
			const Method & mt = *it_method;

			std::string response_name = "Response_" + cl.name +"_" + mt.name;

			m_stream << "class " << response_name << std::endl;
			m_stream << "	: public Axe::Response" << std::endl;

			m_stream << "{" << std::endl;
			m_stream << "pulic:" << std::endl;

			m_stream << "	virtual void response(";
			
			TVectorArguments::const_iterator 
				it_args = mt.outArguments.begin(),
				it_args_end = mt.outArguments.end();

			if( it_args != it_args_end )
			{
				const Argument & ar = *it_args;

				m_stream << " " << writeArgumentType( ar.type.name );

				for( ++it_args; it_args != it_args_end; ++it_args )
				{
					const Argument & ar = *it_args;

					m_stream << ", " << writeArgumentType( ar.type.name ) << " " << ar.name;
				}

				m_stream << " ";
			}

			m_stream << ") = 0;" << std::endl;
			m_stream << std::endl;
			m_stream << "private:" << std::endl;
			m_stream << "	void process( stream_read * _stream ) override;" << std::endl;
			m_stream << "};" << std::endl;
			m_stream << "typedef Axe::SharedPtr<" << response_name << "> " << response_name << "Ptr;" << std::endl; 
			m_stream << std::endl;
		}
	}
	void SLAxeGenerator::generateProxy( const Declaration::Class & _class )
	{
		//class proxy: public proxy_base
		//{
		//public:
		//	proxy( std::size_t _id, connection * _cn );
		//	void add_adapter_async( std::string a0 , std::string a1 , unsigned short a2 , response_add_adapter * _response );
		//	void get_servant_info_async( std::string a0 , response_get_servant_info * _response );
		//	void get_adapter_id_async( size_t a0 , response_get_adapter_id * _response );

		//};

		m_stream << std::endl;

		const Class & cl = _class;

		std::string proxy_name = "Proxy_" + cl.name;

		m_stream << "class " << proxy_name << std::endl;
		m_stream << "	: public Axe::Proxy" << std::endl;

		m_stream << "{" << std::endl;
		m_stream << "pulic:" << std::endl;
		m_stream << "	" << proxy_name << "( std::size_t _id, const Axe::ConnectionPtr & _connection );" << std::endl;
		m_stream << std::endl;
		m_stream << "pulic:" << std::endl;

		for( TVectorMethods::const_iterator
			it_method = cl.methods.begin(),
			it_method_end = cl.methods.end();
		it_method != it_method_end;
		++it_method )
		{
			const Method & mt = *it_method;

			std::string response_name = "Response_" + cl.name +"_" + mt.name + "Ptr";

			m_stream << "	virtual void " << mt.name << "(";

			for( TVectorArguments::const_iterator
				it_args = mt.inArguments.begin(),
				it_args_end = mt.inArguments.end();
			it_args != it_args_end;
			++it_args )
			{
				const Argument & ar = *it_args;

				m_stream << " " << writeArgumentType( ar.type.name ) << " " << ar.name << ",";
			}

			m_stream << " const " << response_name << " & _response );" << std::endl;
		}
		m_stream << "};" << std::endl;

		m_stream << "typedef Axe::SharedPtr<" << proxy_name << "> " << proxy_name << "Ptr;" << std::endl;
	}
	//////////////////////////////////////////////////////////////////////////
	std::string SLAxeGenerator::writeArgumentType( const std::string & _type )
	{
		TSetTypes::iterator it_pod_found = m_podTypes.find( _type );

		if( it_pod_found != m_podTypes.end() )
		{
			return _type;
		}

		TSetTypes::iterator it_spec_found = m_specTypes.find( _type );

		if( it_spec_found != m_specTypes.end() )
		{
			if( _type == "size_t" )
			{
				return "std::size_t";
			}
			else if( _type == "string" )
			{
				return "const std::string &";
			}
		}

		TSetTypes::iterator it_typedef_found = m_typedefTypes.find( _type );

		if( it_typedef_found != m_typedefTypes.end() )
		{
			std::string ret_type = "const ";
			ret_type += _type;
			ret_type += " &";

			return ret_type;
		}

		TSetTypes::iterator it_struct_found = m_structTypes.find( _type );

		if( it_struct_found != m_structTypes.end() )
		{
			std::string ret_type = "const ";
			ret_type += _type;
			ret_type += " &";

			return ret_type;
		}

		TSetTypes::iterator it_class_found = m_classTypes.find( _type );

		if( it_class_found != m_classTypes.end() )
		{
			std::string ret_type = "const ";
			ret_type += _type;
			ret_type += "Prx &";

			return ret_type;
		}

		return "__compiler__type__error";
	}
	//////////////////////////////////////////////////////////////////////////
	std::string SLAxeGenerator::writeMemberType( const std::string & _type )
	{
		TSetTypes::iterator it_spec_found = m_specTypes.find( _type );

		if( it_spec_found != m_specTypes.end() )
		{
			if( _type == "size_t" )
			{
				return "std::size_t";
			}
			else if( _type == "string" )
			{
				return "std::string";
			}
		}

		TSetTypes::iterator it_class_found = m_classTypes.find( _type );

		if( it_class_found != m_classTypes.end() )
		{
			std::string ret_type = _type;
			ret_type += "Prx";

			return ret_type;
		}

		return _type;
	}
	//////////////////////////////////////////////////////////////////////////
	std::string SLAxeGenerator::writeTemplates( const std::string & _type )
	{
		TSetTypes::iterator it_templates_found = m_templatesTypes.find( _type );

		if( it_templates_found != m_templatesTypes.end() )
		{
			std::string ret_type = "std::";
			ret_type += _type;

			return ret_type;
		}

		TSetTypes::iterator it_class_found = m_classTypes.find( _type );

		if( it_class_found != m_classTypes.end() )
		{
			std::string ret_type = _type;
			ret_type += "Prx";

			return ret_type;
		}

		return _type;
	}
}