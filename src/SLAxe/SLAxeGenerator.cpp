#	include "pch.hpp"

#	include "SLAxeParser.hpp"
#	include "SLAxeGenerator.hpp"

namespace Axe
{
	using namespace Axe::Declaration;

	//////////////////////////////////////////////////////////////////////////
	SLAxeGenerator::SLAxeGenerator( SLAxeParser * _parser )
		: m_parser(_parser)
		, m_tabs(0)
		, m_lockTabs(false)
	{
		m_podTypes.insert("bool");
		m_podTypes.insert("char");
		m_podTypes.insert("int");
		m_podTypes.insert("float");

		m_specTypes.insert("size_t");
		m_specTypes.insert("string");
		m_specTypes.insert("Archive");

		m_templatesTypes.insert("map");
		m_templatesTypes.insert("list");
		m_templatesTypes.insert("vector");
		m_templatesTypes.insert("set");

		m_classTypes.insert("Servant");

		const Namespace & ns = m_parser->getNamespace();

		typegen( ns );
	}
	void SLAxeGenerator::typegen( const Declaration::Namespace & ns )
	{
		const TVectorTypedefs & typedefs = ns.typedefs;

		for( TVectorTypedefs::const_iterator
			it_typedef = typedefs.begin(),
			it_typedef_end = typedefs.end();
		it_typedef != it_typedef_end;
		++it_typedef )
		{
			const Typedef & td = *it_typedef;

			m_typedefTypes.insert( td.name );
		}

		const TVectorClasses & classes = ns.classes;

		for( TVectorClasses::const_iterator
			it_class = classes.begin(),
			it_class_end = classes.end();
		it_class != it_class_end;
		++it_class )
		{
			const Class & cl = *it_class;

			m_classTypes.insert(cl.name);
		}

		const TVectorStructs & structs = ns.structs;

		for( TVectorStructs::const_iterator
			it_struct = structs.begin(),
			it_struct_end = structs.end();
		it_struct != it_struct_end;
		++it_struct )
		{
			const Struct & st = *it_struct;

			m_structTypes.insert(st.name);
		};

		const TVectorNamespaces & namespaces = ns.namespaces;

		for( TVectorNamespaces::const_iterator
			it_namespace = namespaces.begin(),
			it_namespace_end = namespaces.end();
		it_namespace != it_namespace_end;
		++it_namespace )
		{
			this->typegen( *it_namespace );
		}
	}
	//////////////////////////////////////////////////////////////////////////
	std::stringstream & SLAxeGenerator::getStream()
	{
		return m_stream;
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::generateHeader( const std::string & _path, const std::string & _fileName )
	{
		m_stream.str("");

		m_stream << "#	pragma once" << std::endl;
		m_stream << std::endl;

		m_stream << "#	include <Axe/Bellhop.hpp>" << std::endl;
		m_stream << "#	include <Axe/Servant.hpp>" << std::endl;
		m_stream << "#	include <Axe/Response.hpp>" << std::endl;
		m_stream << "#	include <Axe/Proxy.hpp>" << std::endl;
		m_stream << "#	include <Axe/Response.hpp>" << std::endl;
		m_stream << "#	include <Axe/Exception.hpp>" << std::endl;

		const TVectorIncludes & includes = m_parser->getIncludes();

		generateHeaderIncludes( includes, _path );

		m_stream << std::endl;

		m_stream << "namespace Axe" << std::endl;
		m_stream << "{" << std::endl;
		m_stream << "	class ArchiveInvocation;" << std::endl;
		m_stream << "	class ArchiveDispatcher;" << std::endl;
		m_stream << "}" << std::endl;
		m_stream << std::endl;

		const Namespace & ns = m_parser->getNamespace();

		generateHeaderNamespace( ns );
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::generateHeaderIncludes( const Declaration::TVectorIncludes & _includes, const std::string & _path )
	{
		if( _includes.empty() == true )
		{
			return;
		}

		write() << std::endl;

		for( TVectorIncludes::const_iterator
			it_include = _includes.begin(),
			it_include_end = _includes.end();
		it_include != it_include_end;
		++it_include )
		{
			write() << "#	include <" << _path << it_include->path << ".hpp>" << std::endl;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::generateHeaderNamespace( const Declaration::Namespace & _namespace )
	{
		if( _namespace.name.empty() == false )
		{
			write() << "namespace " << _namespace.name << std::endl;
			write() << "{" << std::endl;
			increfTabs();
		}

		const TVectorOrder & order = _namespace.order;

		const TVectorTypedefs & typedefs = _namespace.typedefs;
		const TVectorStructs & structs = _namespace.structs;
		const TVectorClasses & classes = _namespace.classes;
		const TVectorExceptions & exceptions = _namespace.exceptions;
		const TVectorNamespaces & namespaces = _namespace.namespaces;

		TVectorTypedefs::const_iterator it_typedef = typedefs.begin();
		TVectorStructs::const_iterator it_struct = structs.begin();
		TVectorClasses::const_iterator it_class = classes.begin();
		TVectorExceptions::const_iterator it_exception = exceptions.begin();
		TVectorNamespaces::const_iterator it_namespace = namespaces.begin();

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
					generateHeaderTypedef( *it_typedef );
					++it_typedef;
				}break;
			case DECL_STRUCT:
				{
					generateHeaderStruct( *it_struct );
					++it_struct;
				}break;
			case DECL_CLASS:
				{
					generateHeaderClass( *it_class );
					++it_class;
				}break;
			case DECL_EXCEPTION:
				{
					generateHeaderException( *it_exception );
					++it_exception;
				}break;
			case DECL_NAMESPACE:
				{
					generateHeaderNamespace( *it_namespace );
					++it_namespace;
				}break;
			}
		}

		if( _namespace.name.empty() == false )
		{
			decrefTabs();
			write() << "}" << std::endl;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::generateHeaderStruct( const Struct & _struct )
	{
		write() << std::endl;

		const Struct & st = _struct;

		write() << "struct " + st.name << std::endl;

		TVectorParents::const_iterator
			it_parent = st.parents.begin(),
			it_parent_end = st.parents.end();

		if( it_parent != it_parent_end )
		{
			write() << "	: " << it_parent->inheritance << " " << it_parent->name << std::endl;

			for( ++it_parent ; it_parent != it_parent_end; ++it_parent )
			{
				const Parent & pr = *it_parent;

				write() << "	, " << it_parent->inheritance << " " << it_parent->name << std::endl;
			}
		}


		write() <<	"{" << std::endl;

		for( TVectorMembers::const_iterator
			it_member = st.members.begin(),
			it_member_end = st.members.end();
		it_member != it_member_end;
		++it_member )
		{
			const Member & mb = *it_member;

			write() << "	" << writeMemberType( mb.type.name ) << " " << mb.name << ";" << std::endl;
		}

		write() << "};" << std::endl;

		write() << std::endl;

		write() << "void operator << ( Axe::ArchiveInvocation & ar, const " << st.name << " & _value );" << std::endl;
		write() << "void operator >> ( Axe::ArchiveDispatcher & ar, " << st.name << " & _value );" << std::endl;
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::generateHeaderTypedef( const Typedef & _typedef )
	{
		write() << std::endl;

		const Typedef & td = _typedef;

		write() << "typedef " << writeTemplates( td.type );

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
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::generateHeaderException( const Exception & _ex )
	{
		write() << std::endl;

		write() << "class " + _ex.name << std::endl;
		write() << "	: virtual public Axe::Exception" << std::endl;


		for( TVectorParents::const_iterator
			it_parent = _ex.parents.begin(),
			it_parent_end = _ex.parents.end();
		it_parent != it_parent_end; 
		++it_parent )
		{
			const Parent & pr = *it_parent;
			write() << "	, " << it_parent->inheritance << " " << it_parent->name << std::endl;
		}

		write() << "{" << std::endl;
		write() << "public:" << std::endl;
		write() << "	void rethrow() const override;" << std::endl;
		write() << std::endl;
		write() <<	"public:" << std::endl;

		for( TVectorMembers::const_iterator
			it_member = _ex.members.begin(),
			it_member_end = _ex.members.end();
		it_member != it_member_end;
		++it_member )
		{
			const Member & mb = *it_member;

			write() << "	" << writeMemberType( mb.type.name ) << " " << mb.name << ";" << std::endl;
		}

		write() << std::endl;
		write() << "public:" << std::endl;
		write() << "	void write( Axe::ArchiveInvocation & _ar ) const override;" << std::endl;
		write() << "	void read( Axe::ArchiveDispatcher & _ar ) override;" << std::endl;
		write() << "};" << std::endl;

		write() << std::endl;
		writeTypedefHandle( _ex.name );
		write() << std::endl;
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::generateHeaderClass( const Declaration::Class & _class )
	{
		generateHeaderServant( _class );
		generateHeaderBellhop( _class );		
		generateHeaderResponse( _class );
		generateHeaderProxy( _class );
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::generateHeaderBellhop( const Class & _class )
	{
		write() << std::endl;

		const Class & cl = _class;

		for( TVectorMethods::const_iterator
			it_method = cl.methods.begin(),
			it_method_end = cl.methods.end();
		it_method != it_method_end;
		++it_method )
		{
			const Method & mt = *it_method;

			std::string bellhop_name = writeBellhopName( cl.name, mt.name );
			std::string servant_name = writeServantName( cl.name );

			write() << "class " << bellhop_name << std::endl;
			write() << "	: public Axe::Bellhop" << std::endl;
			write() << "{" << std::endl;
			write() << "public:" << std::endl;
			write() << "	" << bellhop_name << "( std::size_t _requestId, const Axe::SessionPtr & _session, const " << servant_name << "Ptr & _servant );" << std::endl;
			write() << std::endl;
			write() << "public:" << std::endl;
			write() << "	void response(";

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
			write() << std::endl;
			write() << "	void throw_exception( const Axe::Exception & _ex );" << std::endl;
			write() << std::endl;
			write() << "protected:" << std::endl;
			write() << "	" << servant_name << "Ptr m_servant;" << std::endl;
			write() << "};" << std::endl;
			write() << std::endl;
			writeTypedefHandle( bellhop_name );			
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::generateHeaderServant( const Declaration::Class & _class )
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

		write() << std::endl;

		const Class & cl = _class;

		for( TVectorMethods::const_iterator
			it_method = cl.methods.begin(),
			it_method_end = cl.methods.end();
		it_method != it_method_end;
		++it_method )
		{
			const Method & mt = *it_method;
			std::string bellhop_name = writeBellhopName( cl.name, mt.name );
			write() << "typedef AxeHandle<class " << bellhop_name << "> " << bellhop_name << "Ptr;" << std::endl;
		}

		write() << std::endl;

		std::string servant_name = writeServantName( cl.name );

		write() << "class " << servant_name << std::endl;

		if( cl.parents.empty() == true )
		{
			write() << "	: virtual public Axe::Servant" << std::endl;
		}
		else
		{
			TVectorParents::const_iterator 
				it_parent = cl.parents.begin(),
				it_parent_end = cl.parents.end();

			if( it_parent != it_parent_end )
			{
				const Parent & pr = *it_parent;

				std::string parent_name = writeServantName( pr.name );

				write() << "	: " << pr.inheritance << " " << parent_name << std::endl;

				for( ++it_parent; it_parent != it_parent_end; ++it_parent )
				{
					const Parent & pr = *it_parent;

					std::string parent_name = writeServantName( pr.name );

					write() << "	, " << pr.inheritance << " " << parent_name << std::endl;
				}
			}
		}

		write() << "{" << std::endl;

		if( cl.methods.empty() == false )
		{
			write() << "public:" << std::endl;

			for( TVectorMethods::const_iterator
				it_method = cl.methods.begin(),
				it_method_end = cl.methods.end();
			it_method != it_method_end;
			++it_method )
			{
				const Method & mt = *it_method;

				std::string bellhop_name = writeBellhopName( cl.name, mt.name ) + "Ptr";

				write() << "	virtual void " << mt.name << "_async( const " << bellhop_name << " & _cb";

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


			write() << std::endl;
			write() << "protected:" << std::endl;

			for( TVectorMembers::const_iterator
				it_member = cl.members.begin(),
				it_member_end = cl.members.end();
			it_member != it_member_end;
			++it_member )
			{
				write() << "	" << writeMemberType( it_member->type.name ) << " " << it_member->name << ";" << std::endl;
			}

			write() << std::endl;
			//write() << "public:" << std::endl;
			//write() << "	void writeException( Axe::ArchiveInvocation & _ar, std::size_t _methodId, const Axe::Exception & _ex );" << std::endl;
			write() << std::endl;
			write() << "private:" << std::endl;
			write() << "	void callMethod( std::size_t _methodId , std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session ) override;" << std::endl;

			write() << "	void responseException( std::size_t _methodId, std::size_t _requestId, const SessionPtr & _session, const Exception & _ex ) override;" << std::endl;
		}

		write() << "};" << std::endl;
		write() << std::endl;
		writeTypedefHandle( servant_name );
		write() << std::endl;
		write() << "void operator << ( Axe::ArchiveInvocation & _ar, const " << servant_name << "Ptr & _value );" << std::endl;
		write() << std::endl;
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::generateHeaderResponse( const Declaration::Class & _class )
	{
		//class response_add_adapter
		//	: public response_base
		//{
		//public:
		//	virtual void response( std::size_t ) = 0;
		//private:
		//	void response_call( stream_read * _stream ) override;
		//};

		write() << std::endl;

		const Class & cl = _class;

		for( TVectorMethods::const_iterator
			it_method = cl.methods.begin(),
			it_method_end = cl.methods.end();
		it_method != it_method_end;
		++it_method )
		{
			const Method & mt = *it_method;

			std::string response_name = writeResponseName( cl.name, mt.name );

			writeLine();

			write() << "class " << response_name << std::endl;
			write() << "	: public Axe::Response" << std::endl;

			write() << "{" << std::endl;
			write() << "protected:" << std::endl;

			write() << "	virtual void response(";

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
			write() << std::endl;
			write() << "public:" << std::endl;
			write() << "	void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;" << std::endl;
			write() << "	void exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;" << std::endl;
			write() << "};" << std::endl;
			write() << std::endl;
			writeTypedefHandle( response_name );

			write() << std::endl;

			write() << "template<>" << std::endl;
			write() << "class BindResponse<" << response_name << "Ptr>" << std::endl;
			write() << "	: public " << response_name << std::endl;
			write() << "{" << std::endl;
			write() << "	typedef boost::function<void(";

			{
				TVectorArguments::const_iterator
					it_arg = mt.outArguments.begin(),
					it_arg_end = mt.outArguments.end();

				if( it_arg != it_arg_end )
				{
					m_stream << writeArgumentType( it_arg->type.name );

					for( ++it_arg; it_arg != it_arg_end; ++it_arg )
					{
						m_stream << ", " << writeArgumentType( it_arg->type.name );
					}
				}
			}

			m_stream << ")> TBindResponse;" << std::endl;

			write() << "	typedef boost::function<void(const Axe::Exception &)> TBindException;" << std::endl;
			write() << std::endl;
			write() << "public:" << std::endl;
			write() << "	BindResponse( const TBindResponse & _response, const TBindException & _exception );" << std::endl;
			write() << std::endl;
			write() << "public:" << std::endl;

			//	void response( int _i, float _f ) override
			//	{
			//		m_response( _i, _f );
			//	}

			write() << "	void response(";

			{
				std::size_t bellhop_args = 0;

				TVectorArguments::const_iterator 
					it_args = mt.outArguments.begin(),
					it_args_end = mt.outArguments.end();

				if( it_args != it_args_end )
				{
					const Argument & ar = *it_args;

					m_stream << " " << writeArgumentType( ar.type.name ) << " _arg" << bellhop_args;
					++bellhop_args;

					for( ++it_args; it_args != it_args_end; ++it_args )
					{
						const Argument & ar = *it_args;

						m_stream << ", " << writeArgumentType( ar.type.name ) << " _arg" << bellhop_args;
						++bellhop_args;
					}

					m_stream << " ";
				}
			}

			m_stream << ") override;" << std::endl;

			write() << std::endl;
			write() << "	void throw_exception( const Axe::Exception & _ex ) override;" << std::endl;
			write() << std::endl;
			write() << "protected:" << std::endl;
			write() << "	TBindResponse m_response;" << std::endl;
			write() << "	TBindException m_exception;" << std::endl;
			write() << "};" << std::endl;
		}
	}
	void SLAxeGenerator::generateHeaderProxy( const Declaration::Class & _class )
	{
		//class proxy: public proxy_base
		//{
		//public:
		//	proxy( std::size_t _id, connection * _cn );
		//	void add_adapter_async( std::string a0 , std::string a1 , unsigned short a2 , response_add_adapter * _response );
		//	void get_servant_info_async( std::string a0 , response_get_servant_info * _response );
		//	void get_adapter_id_async( size_t a0 , response_get_adapter_id * _response );

		//};

		write() << std::endl;

		const Class & cl = _class;

		std::string proxy_name = writeProxyName( cl.name );

		write() << "class " << proxy_name << std::endl;

		if( cl.parents.empty() == true )
		{
			write() << "	: virtual public Axe::Proxy" << std::endl;
		}
		else
		{
			TVectorParents::const_iterator 
				it_parent = cl.parents.begin(),
				it_parent_end = cl.parents.end();

			if( it_parent != it_parent_end )
			{
				const Parent & pr = *it_parent;

				std::string parent_name = writeProxyName( pr.name );

				write() << "	:	" << pr.inheritance << " " << parent_name << std::endl;

				for( ++it_parent; it_parent != it_parent_end; ++it_parent )
				{
					const Parent & pr = *it_parent;

					std::string parent_name = writeProxyName( pr.name );

					write() << "	,	" << pr.inheritance << " " << parent_name << std::endl;
				}
			}
		}

		write() << "{" << std::endl;
		write() << "public:" << std::endl;
		write() << "	" << proxy_name << "( std::size_t _id, const Axe::ConnectionPtr & _connection );" << std::endl;
		write() << std::endl;
		write() << "public:" << std::endl;

		for( TVectorMethods::const_iterator
			it_method = cl.methods.begin(),
			it_method_end = cl.methods.end();
		it_method != it_method_end;
		++it_method )
		{
			const Method & mt = *it_method;

			std::string response_name = writeResponseName( cl.name, mt.name ) + "Ptr";

			write() << "	void " << mt.name << "_async( const " << response_name << " & _response";

			for( TVectorArguments::const_iterator
				it_args = mt.inArguments.begin(),
				it_args_end = mt.inArguments.end();
			it_args != it_args_end;
			++it_args )
			{
				const Argument & ar = *it_args;

				m_stream << ", " << writeArgumentType( ar.type.name ) << " " << ar.name;
			}

			m_stream << " );" << std::endl;			
		}

		write() << "};" << std::endl;
		write() << std::endl;

		//write() << "void operator << ( Axe::ArchiveInvocation & ar, const " << proxy_name << " & _value );" << std::endl;
		//write() << "void operator >> ( Axe::ArchiveDispatcher & ar, " << proxy_name << " & _value );" << std::endl;
		/*write() << std::endl;*/

		writeTypedefHandle( proxy_name );
		write() << std::endl;
		write() << "void operator << ( Axe::ArchiveInvocation & _ar, const " << proxy_name << "Ptr & _value );" << std::endl;

	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::generateImplement( const std::string & _fileName )
	{
		m_stream.str("");

		m_stream << "#	include \"pch.hpp\"" << std::endl;
		m_stream << std::endl;
		m_stream << "#	include \"" << _fileName << ".hpp\"" << std::endl;
		m_stream << std::endl;
		m_stream << "#	include <Axe/ArchiveInvocation.hpp>" << std::endl;
		m_stream << "#	include <Axe/ArchiveDispatcher.hpp>" << std::endl;
		m_stream << std::endl;

		const Namespace & ns = m_parser->getNamespace();

		generateImplementNamespace( ns );
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::generateImplementNamespace( const Namespace & _namespace )
	{
		if( _namespace.name.empty() == false )
		{
			write() << "namespace " << _namespace.name << std::endl;
			write() << "{" << std::endl;
			increfTabs();
		}

		const TVectorOrder & order = _namespace.order;

		const TVectorStructs & structs = _namespace.structs;
		const TVectorClasses & classes = _namespace.classes;
		const TVectorExceptions & exceptions = _namespace.exceptions;
		const TVectorNamespaces & namespaces = _namespace.namespaces;

		TVectorStructs::const_iterator it_struct = structs.begin();
		TVectorClasses::const_iterator it_class = classes.begin();
		TVectorExceptions::const_iterator it_exception = exceptions.begin();

		TVectorNamespaces::const_iterator it_namespace = namespaces.begin();

		for( TVectorOrder::const_iterator
			it_order = order.begin(),
			it_order_end = order.end();
		it_order != it_order_end;
		++it_order )
		{
			switch( *it_order )
			{
			case DECL_STRUCT:
				{
					generateImplementStruct( *it_struct );
					++it_struct;
				}break;
			case DECL_CLASS:
				{
					generateImplementClass( *it_class );
					++it_class;
				}break;
			case DECL_EXCEPTION:
				{
					generateImplementException( *it_exception );
					++it_exception;
				}break;
			case DECL_NAMESPACE:
				{
					generateImplementNamespace( *it_namespace );
					++it_namespace;
				}break;
			}
		}

		if( _namespace.name.empty() == false )
		{
			decrefTabs();
			write() << "}" << std::endl;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::generateImplementStruct( const Struct & _struct )
	{
		//write() << std::endl;

		const Struct & st = _struct;

		writeLine();
		write() << "void operator << ( Axe::ArchiveInvocation & ar, const " << st.name << " & _value )" << std::endl;
		write() <<	"{" << std::endl;

		for( TVectorParents::const_iterator
			it_parent = st.parents.begin(),
			it_parent_end = st.parents.end();
		it_parent != it_parent_end;
		++it_parent )
		{
			const Parent & pr = *it_parent;

			write() << "	ar << static_cast<const " << pr.name << " &>( _value );" << std::endl;
		}

		for( TVectorMembers::const_iterator
			it_member = st.members.begin(),
			it_member_end = st.members.end();
		it_member != it_member_end;
		++it_member )
		{
			const Member & mb = *it_member;

			write() << "	ar << _value." << mb.name << ";" << std::endl;
		}

		write() << "}" << std::endl;

		writeLine();
		write() << "void operator >> ( Axe::ArchiveDispatcher & ar, " << st.name << " & _value )" << std::endl;
		write() <<	"{" << std::endl;

		for( TVectorParents::const_iterator
			it_parent = st.parents.begin(),
			it_parent_end = st.parents.end();
		it_parent != it_parent_end;
		++it_parent )
		{
			const Parent & pr = *it_parent;

			write() << "	ar >> static_cast<const " << pr.name << " &>( _value );" << std::endl;
		}

		for( TVectorMembers::const_iterator
			it_member = st.members.begin(),
			it_member_end = st.members.end();
		it_member != it_member_end;
		++it_member )
		{
			const Member & mb = *it_member;

			write() << "	";
			writeReadType( "ar", mb.type.name, "_value." + mb.name );
		}

		write() << "}" << std::endl;
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::generateImplementClass( const Class & _class )
	{
		generateImplementServant( _class );
		generateImplementBellhop( _class );		
		generateImplementResponse( _class );
		generateImplementProxy( _class );
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::generateImplementException( const Declaration::Exception & _ex )
	{
		write() << std::endl;
		writeLine();

		write() << "void " << _ex.name << "::rethrow() const" << std::endl;
		write() << "{" << std::endl;
		write() << "	throw *this;" << std::endl;
		write() << "}" << std::endl;
		writeLine();
		write() << "void " << _ex.name << "::write( Axe::ArchiveInvocation & _ar ) const" << std::endl;
		write() << "{" << std::endl;

		for( TVectorParents::const_iterator
			it_parent = _ex.parents.begin(),
			it_parent_end = _ex.parents.end();
		it_parent != it_parent_end;
		++it_parent )
		{
			const Parent & pr = *it_parent;

			write() << "	" << pr.name << "::write( _ar );" << std::endl;
		}

		for( TVectorMembers::const_iterator
			it_member = _ex.members.begin(),
			it_member_end = _ex.members.end();
		it_member != it_member_end;
		++it_member )
		{
			const Member & mb = *it_member;

			write() << "	_ar << " << mb.name << ";" << std::endl;
		}

		write() << "}" << std::endl;
		writeLine();
		write() << "void " << _ex.name << "::read( Axe::ArchiveDispatcher & _ar )" << std::endl;
		write() << "{" << std::endl;

		for( TVectorParents::const_iterator
			it_parent = _ex.parents.begin(),
			it_parent_end = _ex.parents.end();
		it_parent != it_parent_end;
		++it_parent )
		{
			const Parent & pr = *it_parent;

			write() << "	" << pr.name << "::read( _ar );" << std::endl;
		}

		for( TVectorMembers::const_iterator
			it_member = _ex.members.begin(),
			it_member_end = _ex.members.end();
		it_member != it_member_end;
		++it_member )
		{
			const Member & mb = *it_member;

			write() << "	";
			writeReadType( "_ar", mb.type.name, mb.name );			
		}

		write() << "}" << std::endl;
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::generateImplementBellhop( const Class & _class )
	{
		//bellhop_add_adapter::bellhop_add_adapter ( std::size_t _requestId, adapter_session * _session )
		//	: bellhop(_requestId, _session){}
		//void bellhop_add_adapter ::response( std::size_t a0 )
		//{
		//	stream_write * ssocket = m_session->begin_response( m_requestId );
		//	ssocket->write( a0 );
		//	m_session->procces();
		//}

		//write() << std::endl;

		const Class & cl = _class;

		for( TVectorMethods::const_iterator
			it_method = cl.methods.begin(),
			it_method_end = cl.methods.end();
		it_method != it_method_end;
		++it_method )
		{
			const Method & mt = *it_method;

			std::string bellhop_name = writeBellhopName( cl.name, mt.name );
			std::string servant_name = writeServantName( cl.name );

			writeLine();
			write() << bellhop_name << "::" << bellhop_name << "( std::size_t _requestId, const Axe::SessionPtr & _session, const " << servant_name << "Ptr & _servant )" << std::endl;
			write() <<	"	: Axe::Bellhop(_requestId, _session)" << std::endl;
			write() <<	"	, m_servant(_servant)" << std::endl;
			write() << "{" << std::endl;
			write() << "}" << std::endl;
			writeLine();
			write() << "void " << bellhop_name << "::response(";

			std::size_t arg_enumerator = 0;

			TVectorArguments::const_iterator 
				it_args = mt.outArguments.begin(),
				it_args_end = mt.outArguments.end();

			if( it_args != it_args_end )
			{
				const Argument & ar = *it_args;

				m_stream << " " << writeArgumentType( ar.type.name ) << " _arg" << arg_enumerator;
				++arg_enumerator;

				for( ++it_args; it_args != it_args_end; ++it_args )
				{
					const Argument & ar = *it_args;

					m_stream << ", " << writeArgumentType( ar.type.name ) << " _arg" << arg_enumerator;
					++arg_enumerator;
				}

				m_stream << " ";
			}

			m_stream << ")" << std::endl;
			write() << "{" << std::endl;
			write() << "	Axe::ArchiveInvocation & ar = m_session->beginResponse( m_requestId );" << std::endl;

			arg_enumerator = 0;

			for( TVectorArguments::const_iterator
				it_args = mt.outArguments.begin(),
				it_args_end = mt.outArguments.end();
			it_args != it_args_end;
			++it_args )
			{
				const Argument & ar = *it_args;

				write() << "	ar << _arg" << arg_enumerator << ";" << std::endl;
				++arg_enumerator;
			}

			write() << "	m_session->process();" << std::endl;
			write() << "}" << std::endl;
			writeLine();
			write() << "void " << bellhop_name << "::throw_exception( const Axe::Exception & _ex )" << std::endl;
			write() << "{" << std::endl;
			write() << "	Axe::ArchiveInvocation & ar = m_session->beginException( m_requestId );" << std::endl;
			write() << "	s_" << servant_name << "_writeException_" << mt.name << "( ar, _ex );" << std::endl;
			write() << "	m_session->process();" << std::endl;
			write() << "}" << std::endl;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::generateImplementServant( const Class & _class )
	{
		//	const int enum_method_add_adapter = 0;

		//	void servant::call_method( std::size_t _methodId, std::size_t _requestId, adapter_session * _session )
		//	{
		//		stream_read * stream = _session->get_streamIn();
		//		switch( _methodId ){
		//case enum_method_add_adapter:
		// {
		//	 bellhop_add_adapter * bellhop
		//		 = new bellhop_add_adapter( _requestId, _session );
		//	 std::string * a0;
		//	 stream->select( &a0 );

		//	 this->add_adapter ( bellhop , *a0 , *a1 , *a2 );
		// }break;
		//		}
		//	}

		//write() << std::endl;

		const Class & cl = _class;

		std::string servant_name = writeServantName( cl.name );

		//write() << "enum" << std::endl;
		//write() << "{" << std::endl;
		//write() << "	ESMD_" << cl.name << " = 0" << std::endl;

		//for( TVectorMethods::const_iterator
		//	it_method = cl.methods.begin(),
		//	it_method_end = cl.methods.end();
		//it_method != it_method_end;
		//++it_method )
		//{
		//	const Method & mt = *it_method;
		//	write() << "	,	" << writeEnumMethodName( cl.name, mt.name ) << std::endl;
		//}

		//write() << "};" << std::endl;
		//write() << std::endl;

		if( cl.methods.empty() == false )
		{
			for( TVectorMethods::const_iterator
				it_method = cl.methods.begin(),
				it_method_end = cl.methods.end();
			it_method != it_method_end;
			++it_method )
			{
				const Method & mt = *it_method;

				writeLine();
				write() << "void s_" << servant_name << "_callMethod_" << mt.name << "( " << servant_name << " * _servant, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )" << std::endl;
				write() << "{" << std::endl;
				write() << "	" << writeBellhopName( cl.name, mt.name ) << "Ptr bellhop = new " << writeBellhopName( cl.name, mt.name ) << "( _requestId, _session, _servant );" << std::endl;
				write() << std::endl;
				//write() << "	Axe::ArchiveDispatcher & ar = _session->getArchiveDispatcher();" << std::endl;

				unsigned int bellhop_args = 0;

				for( TVectorArguments::const_iterator
					it_arg = mt.inArguments.begin(),
					it_arg_end = mt.inArguments.end();
				it_arg != it_arg_end;
				++it_arg )
				{
					const Argument & ar = *it_arg;

					write() << "	";
					writeSelectType( "_archive", ar.type.name, bellhop_args );
					++bellhop_args;
				}

				write() << std::endl;
				write() << "	_servant->" << mt.name << "_async( bellhop";

				bellhop_args = 0;

				for( TVectorArguments::const_iterator
					it_arg = mt.inArguments.begin(),
					it_arg_end = mt.inArguments.end();
				it_arg != it_arg_end;
				++it_arg )
				{
					m_stream << ", arg" << bellhop_args;
					++bellhop_args;
				}

				m_stream << " );" << std::endl;

				write() << "}" << std::endl;
			}

			std::string typedef_servant_method = "T" + servant_name + "_callMethod";

			writeLine();
			write() << "typedef void (*" << typedef_servant_method << ")( " << servant_name << " * _servant, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session );" << std::endl;
			writeLine();
			write() << "static " << typedef_servant_method << " s_" << servant_name << "_callMethods[] =" << std::endl;
			write() << "{" << std::endl;
			write() << "	0" << std::endl;

			for( TVectorMethods::const_iterator
				it_method = cl.methods.begin(),
				it_method_end = cl.methods.end();
			it_method != it_method_end;
			++it_method )
			{
				const Method & mt = *it_method;
				write() << "	, &s_" << servant_name << "_callMethod_" << it_method->name << std::endl;
			}

			write() << "};" << std::endl;

			writeLine();
			write() << "void " << servant_name << "::callMethod( std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )" << std::endl;
			write() << "{" << std::endl;

			//		stream_read * stream = _session->get_streamIn();
			//		switch( _methodId ){

			if( cl.methods.empty() == false )
			{
				write() << "	(*s_" << servant_name << "_callMethods[ _methodId ])( this, _requestId, _archive, _session );" << std::endl;
			}

			write() << "}" << std::endl;

			if( cl.methods.empty() == false )
			{
				for( TVectorMethods::const_iterator 
					it_method = cl.methods.begin(), 
					it_method_end = cl.methods.end();
				it_method != it_method_end;
				++it_method	)
				{
					const Method & mt = *it_method;

					writeLine();
					write() << "static void s_" << servant_name << "_writeException_" << mt.name << "( Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )" << std::endl;
					write() << "{" << std::endl;

					if( mt.exceptions.empty() == false )
					{
						write() << "	try" << std::endl;
						write() << "	{" << std::endl;
						write() << "		_ex.rethrow();" << std::endl;
						write() << "	}" << std::endl;

						std::size_t methodExceptionEnumerator = 3;

						for( TVectorMethodExceptions::const_iterator 
							it_exception = mt.exceptions.begin(),
							it_exception_end = mt.exceptions.end();
						it_exception != it_exception_end;
						++it_exception )
						{
							const MethodException & me = *it_exception;

							write() << "	catch( const " << me.name << " & _ex )" << std::endl;
							write() << "	{" << std::endl;
							write() << "		_ar.writeSize( " << methodExceptionEnumerator << " );" << std::endl;
							write() << "		_ex.write( _ar );" << std::endl;
							write() << "	}" << std::endl;		
						}

						write() << "	catch( ... )" << std::endl;
						write() << "	{" << std::endl;
						write() << "		Axe::writeExceptionFilter( _ar );" << std::endl;
						write() << "	}" << std::endl;
					}
					else
					{
						//unknown exeption filter
						write() << "	Axe::writeExceptionFilter( _ar );" << std::endl;
					}

					write() << "}" << std::endl;
				}

				std::string typedef_servant_exception = "T" + servant_name + "_writeException";

				writeLine();
				write() << "typedef void (*" << typedef_servant_exception << ")( Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );" << std::endl;
				writeLine();
				write() << "static " << typedef_servant_exception << " s_" << servant_name << "_writeExceptions[] =" << std::endl;
				write() << "{" << std::endl;
				write() << "	0" << std::endl;

				for( TVectorMethods::const_iterator
					it_method = cl.methods.begin(),
					it_method_end = cl.methods.end();
				it_method != it_method_end;
				++it_method )
				{
					const Method & mt = *it_method;
					write() << "	, &s_" << servant_name << "_writeException_" << it_method->name << std::endl;
				}

				write() << "};" << std::endl;
			}

			writeLine();
			write() << "void " << servant_name << "::responseException( std::size_t _methodId, std::size_t _requestId, const SessionPtr & _session, const Exception & _ex )" << std::endl;
			write() << "{" << std::endl;
			write() << "	Axe::ArchiveInvocation & aw = _session->beginException( _requestId );" << std::endl;		
			write() << std::endl;
			write() << "	(*s_" << servant_name << "_writeExceptions[ _methodId ])( aw, _ex );" << std::endl;
			write() << std::endl;
			write() << "	_session->process();" << std::endl;
			write() << "}" << std::endl;
		}

		//if( cl.methods.empty() == false )
		//{
		//	bool havemethods = false;

		//	for( TVectorMethods::const_iterator 
		//		it_method = cl.methods.begin(), 
		//		it_method_end = cl.methods.end();
		//	it_method != it_method_end;
		//	++it_method	)
		//	{
		//		const Method & mt = *it_method;

		//		if( mt.exceptions.empty() == false )
		//		{
		//			if( havemethods == false )
		//			{
		//				write() << "	switch( _methodId )" << std::endl;
		//				write() << "	{" << std::endl;

		//				havemethods = true;
		//			}

		//			write() << "	case " << writeEnumMethodName( cl.name, mt.name ) << ":" << std::endl;
		//			write() << "		{" << std::endl;

		//			write() << "			try" << std::endl;
		//			write() << "			{" << std::endl;
		//			write() << "				_ex.rethrow();" << std::endl;
		//			write() << "			}" << std::endl;

		//			std::size_t methodExceptionEnumerator = 3;

		//			for( TVectorMethodExceptions::const_iterator 
		//				it_exception = mt.exceptions.begin(),
		//				it_exception_end = mt.exceptions.end();
		//			it_exception != it_exception_end;
		//			++it_exception )
		//			{
		//				const MethodException & me = *it_exception;

		//				write() << "			catch( const " << me.name << " & _ex )" << std::endl;
		//				write() << "			{" << std::endl;
		//				write() << "				_ar.writeSize( " << methodExceptionEnumerator << " );" << std::endl;
		//				write() << "				_ex.write( _ar );" << std::endl;
		//				write() << "			}" << std::endl;		
		//			}

		//			write() << "			catch( ... )" << std::endl;
		//			write() << "			{" << std::endl;
		//			write() << "				this->writeExceptionFilter( _ar );" << std::endl;
		//			write() << "			}" << std::endl;
		//			
		//			write() << "		}break;" << std::endl;
		//		}			
		//	}

		//	if( havemethods == true )
		//	{
		//		write() << "	default:" << std::endl;
		//		write() << "		break;" << std::endl;
		//		write() << "	}" << std::endl;
		//	}
		//}

		//write() << "}" << std::endl;

		writeLine();
		write() << "void operator << ( Axe::ArchiveInvocation & _ar, const " << servant_name << "Ptr & _value )" << std::endl;
		write() << "{" << std::endl;
		write() << "	_value->writeProxy( _ar );" << std::endl;
		write() << "}" << std::endl;
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::generateImplementResponse( const Class & _class )
	{
		//void response_add_adapter ::response_call( stream_read * _stream )
		//{
		//	std::size_t * a0;
		//	_stream->select( &a0 );

		//	this->response( *a0 );
		//}

		//template<>
		//class BindResponse<Foo *>
		//	: public Foo
		//{
		//	typedef boost::function<void (int, float)> TBindResponse;
		//	typedef boost::function<void(const std::exception &)> TBindException;

		//public:
		//	BindResponse( const TBindResponse & _response, const TBindException & _exception )
		//		: m_response(_response)
		//		, m_exception(_exception)
		//	{
		//	}

		//public:
		//	void response( int _i, float _f ) override
		//	{
		//		m_response( _i, _f );
		//	}

		//	void throw_exception( const std::exception & _ex ) override
		//	{
		//		m_exception( _ex );
		//	}

		//protected:
		//	TBindResponse m_response;
		//	TBindException m_exception;
		//};

		//write() << std::endl;

		const Class & cl = _class;

		for( TVectorMethods::const_iterator
			it_method = cl.methods.begin(),
			it_method_end = cl.methods.end();
		it_method != it_method_end;
		++it_method )
		{
			const Method & mt = *it_method;

			writeLine();

			std::string bindResponse = "BindResponse<" + writeResponseName( cl.name, mt.name ) + "Ptr>";

			write() << bindResponse << "::BindResponse( const TBindResponse & _response, const TBindException & _exception )" << std::endl;
			write() << "	: m_response(_response)" << std::endl;
			write() << "	, m_exception(_exception)" << std::endl;
			write() << "{" << std::endl;
			write() << "}" << std::endl;
			//	void response( int _i, float _f ) override
			//	{
			//		m_response( _i, _f );
			//	}

			writeLine();
			write() << "void " << bindResponse << "::response(";

			{
				std::size_t bellhop_args = 0;

				TVectorArguments::const_iterator 
					it_args = mt.outArguments.begin(),
					it_args_end = mt.outArguments.end();

				if( it_args != it_args_end )
				{
					const Argument & ar = *it_args;

					m_stream << " " << writeArgumentType( ar.type.name ) << " _arg" << bellhop_args;
					++bellhop_args;

					for( ++it_args; it_args != it_args_end; ++it_args )
					{
						const Argument & ar = *it_args;

						m_stream << ", " << writeArgumentType( ar.type.name ) << " _arg" << bellhop_args;
						++bellhop_args;
					}

					m_stream << " ";
				}
			}

			m_stream << ")" << std::endl;

			write() << "{" << std::endl;

			write() << "	m_response(";

			{
				std::size_t bellhop_args = 0;

				TVectorArguments::const_iterator
					it_arg = mt.outArguments.begin(),
					it_arg_end = mt.outArguments.end();

				if( it_arg != it_arg_end )
				{
					m_stream << " _arg" << bellhop_args;
					++bellhop_args;

					for( ++it_arg; it_arg != it_arg_end; ++it_arg )
					{
						m_stream << ", _arg" << bellhop_args;
						++bellhop_args;
					}

					m_stream << " ";
				}
			}

			m_stream << ");" << std::endl;
			write() << "}" << std::endl;
			writeLine();
			write() << "void " << bindResponse << "::throw_exception( const Axe::Exception & _ex )" << std::endl;
			write() << "{" << std::endl;
			write() << "	m_exception( _ex );" << std::endl;
			write() << "}" << std::endl;

			writeLine();
			write() << "void " << writeResponseName( cl.name, mt.name ) << "::responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )" << std::endl;
			write() << "{" << std::endl;


			std::size_t bellhop_args = 0;

			for( TVectorArguments::const_iterator
				it_arg = mt.outArguments.begin(),
				it_arg_end = mt.outArguments.end();
			it_arg != it_arg_end;
			++it_arg )
			{
				const Argument & ar = *it_arg;

				write() << "	";
				writeSelectType( "_ar", ar.type.name, bellhop_args );
				++bellhop_args;
			}

			write() << "	this->response(";

			{
				bellhop_args = 0;

				TVectorArguments::const_iterator
					it_arg = mt.outArguments.begin(),
					it_arg_end = mt.outArguments.end();

				if( it_arg != it_arg_end )
				{
					m_stream << " arg" << bellhop_args;
					++bellhop_args;

					for( ++it_arg; it_arg != it_arg_end; ++it_arg )
					{
						m_stream << ", arg" << bellhop_args;
						++bellhop_args;
					}

					m_stream << " ";
				}
			}

			m_stream << ");" << std::endl;
			write() << "}" << std::endl;
			writeLine();
			write() << "void " << writeResponseName( cl.name, mt.name ) << "::exceptionCall( Axe::ArchiveDispatcher & _ar, std::size_t _size )" << std::endl;
			write() << "{" << std::endl;
			write() << "	std::size_t exceptionId;" << std::endl;
			write() << "	_ar.readSize( exceptionId );" << std::endl;
			write() << std::endl;

			write() << "	if( this->exceptionFilter( exceptionId, _ar ) == true )" << std::endl;
			write() << "	{" << std::endl;
			write() << "		return;" << std::endl;
			write() << "	}" << std::endl;

			if( mt.exceptions.empty() == false )
			{
				write() << std::endl;
				write() << "	switch( exceptionId )" << std::endl;
				write() << "	{" << std::endl;

				std::size_t exceptionEnumerator = 2;

				for( TVectorMethodExceptions::const_iterator
					it_exception = mt.exceptions.begin(),
					it_exception_end = mt.exceptions.end();
				it_exception != it_exception_end;
				++it_exception )
				{
					const MethodException & me = *it_exception;

					write() << "	case " << exceptionEnumerator << ":" << std::endl;
					write() << "		{" << std::endl;
					write() << "			" << me.name << " ex;" << std::endl;
					write() << "			ex.read( _ar );" << std::endl;
					write() << "			this->throw_exception( ex ); " << std::endl;
					write() << "		}" << std::endl;

					++exceptionEnumerator;
				}

				write() << "	};" << std::endl;
			}

			write() << "}" << std::endl;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::generateImplementProxy( const Class & _class )
	{
		//	proxy::proxy( std::size_t _id, connection * _cn )
		//		: proxy_base( _id, _cn){}
		//	void proxy:: add_adapter_async( std::string a0 , std::string a1 , unsigned short a2 , response_add_adapter * _response )
		//	{
		//		stream_write * stream = this->begin_message( enum_method_add_adapter, _response );
		//		stream->write( a0 );
		//		stream->write( a1 );
		//		stream->write( a2 );
		//		this->procces();
		//	}
		//}
		const Class & cl = _class;

		//write() << std::endl;

		std::string proxy_name = writeProxyName( cl.name );

		writeLine();
		write() << proxy_name << "::" << proxy_name << "( std::size_t _id, const Axe::ConnectionPtr & _connection )" << std::endl;

		write() << "	: Axe::Proxy(_id, _connection)" << std::endl;

		for( TVectorParents::const_iterator 
			it_parent = cl.parents.begin(),
			it_parent_end = cl.parents.end();
		it_parent != it_parent_end;
		++it_parent )
		{
			const Parent & pr = *it_parent;

			std::string parent_name = writeProxyName( pr.name );

			write() << "	, " << parent_name << "(_id, _connection)" << std::endl;
		}

		write() << "{" << std::endl;
		write() << "}" << std::endl;

		//write() << std::endl;

		for( TVectorMethods::const_iterator
			it_method = cl.methods.begin(),
			it_method_end = cl.methods.end();
		it_method != it_method_end;
		++it_method )
		{
			const Method & mt = *it_method;

			std::string response_name = writeResponseName( cl.name, mt.name ) + "Ptr";

			writeLine();
			write() << "void " << proxy_name << "::" << mt.name << "_async( const " << response_name << " & _response";

			for( TVectorArguments::const_iterator
				it_args = mt.inArguments.begin(),
				it_args_end = mt.inArguments.end();
			it_args != it_args_end;
			++it_args )
			{
				const Argument & ar = *it_args;

				m_stream << ", " << writeArgumentType( ar.type.name ) << " " << ar.name;
			}

			m_stream << " )" << std::endl;

			write() << "{" << std::endl;

			std::size_t methodId = std::distance( cl.methods.begin(), it_method ) + 1;
			write() << "	Axe::ArchiveInvocation & ar = this->beginMessage( " << methodId << ", _response );" << std::endl;

			for( TVectorArguments::const_iterator
				it_arg = mt.inArguments.begin(),
				it_arg_end = mt.inArguments.end();
			it_arg != it_arg_end;
			++it_arg )
			{
				const Argument & ar = *it_arg;

				write() << "	ar << " << ar.name << ";" << std::endl;
			}

			write() << std::endl;
			write() << "	this->processMessage();" << std::endl;
			write() << "}" << std::endl;
			//write() << std::endl;
		}
		writeLine();
		write() << "void operator << ( Axe::ArchiveInvocation & _ar, const " << proxy_name << "Ptr & _value )" << std::endl;
		write() << "{" << std::endl;
		write() << "	_value->write( _ar );" << std::endl;
		write() << "}" << std::endl;
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::writeTypedefHandle( const std::string & _type )
	{
		write() << "typedef AxeHandle<" << _type << "> " << _type << "Ptr;" << std::endl;
	}
	//////////////////////////////////////////////////////////////////////////
	std::string SLAxeGenerator::writeBellhopName( const std::string & _class, const std::string & _method )
	{
		std::string bellhop_name = "Bellhop_" + _class + "_" + _method;
		return bellhop_name;
	}
	//////////////////////////////////////////////////////////////////////////
	std::string SLAxeGenerator::writeServantName( const std::string & _class )
	{
		std::string servant_name = "Servant_" + _class;
		return servant_name;
	}
	//////////////////////////////////////////////////////////////////////////
	std::string SLAxeGenerator::writeResponseName( const std::string & _class, const std::string & _method )
	{
		std::string response_name = "Response_" + _class +"_" + _method;
		return response_name;		
	}
	//////////////////////////////////////////////////////////////////////////
	std::string SLAxeGenerator::writeProxyName( const std::string & _class )
	{
		if( _class == "Servant" )
		{
			return "Axe::Proxy";
		}
	
		std::string proxy_name = "Proxy_" + _class;

		return proxy_name;
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
			else if( _type == "Archive" )
			{
				return "const AxeUtil::Archive &";
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
			ret_type += writeProxyName(_type);
			ret_type += "Ptr &";

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
			else if( _type == "Archive" )
			{
				return "AxeUtil::Archive";
			}
		}

		TSetTypes::iterator it_class_found = m_classTypes.find( _type );

		if( it_class_found != m_classTypes.end() )
		{
			std::string ret_type = writeProxyName(_type);
			ret_type += "Ptr";

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
			std::string ret_type = writeProxyName(_type);
			ret_type += "Ptr";

			return ret_type;
		}

		return _type;
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::writeSelectType( const std::string & _ar, const std::string & _type, std::size_t _enum )
	{
		TSetTypes::iterator it_class_found = m_classTypes.find( _type );

		if( it_class_found != m_classTypes.end() )
		{
			m_stream << writeProxyName( _type ) << "Ptr arg" << _enum << " = Axe::makeProxy<" << writeProxyName( _type ) << "Ptr>( " << _ar << " );" << std::endl;
		}
		else
		{
			m_stream << writeMemberType( _type ) << " arg" << _enum << "; " << _ar << " >> arg" << _enum << ";" << std::endl;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::writeReadType( const std::string & _ar, const std::string & _type, const std::string & _name )
	{
		TSetTypes::iterator it_class_found = m_classTypes.find( _type );

		if( it_class_found != m_classTypes.end() )
		{
			m_stream << _name << " = Axe::makeProxy<" << writeProxyName( _type ) << "Ptr>( " << _ar << " );" << std::endl;
		}
		else
		{
			m_stream << _ar << " >> " << _name << ";" << std::endl;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::writeLine()
	{
		write() << "//////////////////////////////////////////////////////////////////////////" << std::endl;
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::increfTabs()
	{
		++m_tabs;
	}
	void SLAxeGenerator::decrefTabs()
	{
		--m_tabs;
	}
	//////////////////////////////////////////////////////////////////////////
	std::stringstream & SLAxeGenerator::write()
	{
		for( std::size_t it = 0; it != m_tabs ; ++it )
		{
			m_stream << "	";
		}

		return m_stream;
	}
}