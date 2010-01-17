#	include "pch.hpp"

#	include "SLAxeParser.hpp"
#	include "SLAxeGenerator.hpp"

namespace Axe
{
	using namespace Axe::Declaration;

	//////////////////////////////////////////////////////////////////////////
	SLAxeGenerator::SLAxeGenerator( SLAxeParser * _parser, const TMapParsers & _parsers )
		: m_parser(_parser)
		, m_tabs(0)
		, m_lockTabs(false)
		, m_parsers(_parsers)
	{
		m_podTypes.insert("bool");
		m_podTypes.insert("char");
		m_podTypes.insert("int");
		m_podTypes.insert("float");

		m_specTypes.insert("size_t");
		m_specTypes.insert("string");
		m_specTypes.insert("Archive");
		m_specTypes.insert("Proxy");

		m_templatesTypes.insert("map");
		m_templatesTypes.insert("list");
		m_templatesTypes.insert("vector");
		m_templatesTypes.insert("set");

		const Namespace & ns = m_parser->getNamespace();

		m_namespaceAxe = new Namespace(0);
		m_namespaceAxe->name = "Axe";
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

		Namespace * ns = m_parser->getNamespace();

		generateHeaderNamespace( ns );
		generateHeaderNamespaceHelper( ns );
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
	void SLAxeGenerator::generateHeaderNamespace( Declaration::Namespace * _namespace )
	{
		m_namespace = _namespace;

		if( _namespace->name.empty() == false )
		{
			write() << "namespace " << _namespace->name << std::endl;
			write() << "{" << std::endl;
			increfTabs();
		}

		const TVectorOrder & order = _namespace->order;

		TVectorTypedefs & typedefs = _namespace->typedefs;
		TVectorStructs & structs = _namespace->structs;
		TVectorClasses & classes = _namespace->classes;
		TVectorExceptions & exceptions = _namespace->exceptions;
		TListNamespaces & namespaces = _namespace->namespaces;

		TVectorTypedefs::iterator it_typedef = typedefs.begin();
		TVectorStructs::iterator it_struct = structs.begin();
		TVectorClasses::iterator it_class = classes.begin();
		TVectorExceptions::iterator it_exception = exceptions.begin();
		TListNamespaces::iterator it_namespace = namespaces.begin();

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
					generateHeaderNamespace( &*it_namespace );
					++it_namespace;
				}break;
			}
		}

		if( _namespace->name.empty() == false )
		{
			decrefTabs();
			write() << "}" << std::endl;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::generateHeaderNamespaceHelper( Declaration::Namespace * _namespace )
	{
		m_namespace = m_namespaceAxe;

		if( _namespace->name.empty() == false )
		{
			write() << "namespace Axe" << std::endl;
			write() << "{" << std::endl;
			increfTabs();
		}

		const TVectorOrder & order = _namespace->order;

		TVectorTypedefs & typedefs = _namespace->typedefs;
		TVectorStructs & structs = _namespace->structs;
		TVectorClasses & classes = _namespace->classes;
		TVectorExceptions & exceptions = _namespace->exceptions;
		TListNamespaces & namespaces = _namespace->namespaces;

		TVectorTypedefs::iterator it_typedef = typedefs.begin();
		TVectorStructs::iterator it_struct = structs.begin();
		TVectorClasses::iterator it_class = classes.begin();
		TVectorExceptions::iterator it_exception = exceptions.begin();
		TListNamespaces::iterator it_namespace = namespaces.begin();

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
					generateHeaderStructHelper( *it_struct );
					++it_struct;
				}break;
			case DECL_CLASS:
				{
					generateHeaderClassHelper( *it_class );
					++it_class;
				}break;
			case DECL_NAMESPACE:
				{
					generateHeaderNamespaceHelper( &*it_namespace );
					++it_namespace;
				}break;
			}
		}

		if( _namespace->name.empty() == false )
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
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::generateHeaderStructHelper( const Struct & _struct )
	{
		const Struct & st = _struct;

		std::string struct_namespace = writeNamespaceType( st.owner );

		write() << "void operator << ( Axe::ArchiveInvocation & ar, const " << struct_namespace << st.name << " & _value );" << std::endl;
		write() << "void operator >> ( Axe::ArchiveDispatcher & ar, " << struct_namespace << st.name << " & _value );" << std::endl;
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
		write() << "	: virtual public Axe::ProtocolCallException" << std::endl;


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
	void SLAxeGenerator::generateHeaderClassHelper( const Declaration::Class & _class )
	{
		//class response_add_adapter
		//	: public response_base
		//{
		//public:
		//	virtual void response( std::size_t ) = 0;
		//private:
		//	void response_call( stream_read * _stream ) override;
		//};

		const Class & cl = _class;

		for( TVectorMethods::const_iterator
			it_method = cl.methods.begin(),
			it_method_end = cl.methods.end();
		it_method != it_method_end;
		++it_method )
		{
			const Method & mt = *it_method;

			std::string response_name = writeResponseName( cl.name, mt.name );

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

			write() << "	void throw_exception( const Axe::Exception & _ex ) override;" << std::endl;
			write() << std::endl;
			write() << "protected:" << std::endl;
			write() << "	TBindResponse m_response;" << std::endl;
			write() << "	TBindException m_exception;" << std::endl;
			write() << "};" << std::endl;
		}

		std::string proxy_name = writeProxyName( cl.name );

		write() << std::endl;
		write() << "void operator << ( Axe::ArchiveInvocation & _ar, const " << proxy_name << "Ptr & _value );" << std::endl;
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
			write() << "public:" << std::endl;
			write() << "	void callMethod( std::size_t _methodId , std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session ) override;" << std::endl;
			write() << "	void responseException( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const Axe::Exception & _ex ) override;" << std::endl;
			write() << "public:" << std::endl;
			write() << "	void writeExceptions_( std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );" << std::endl;
		}

		if( cl.members.empty() == false )
		{
			write() << std::endl;
			write() << "protected:" << std::endl;
			write() << "	void _restore( Axe::ArchiveDispatcher & _ar ) override;" << std::endl;
			write() << "	void _evict( Axe::ArchiveInvocation & _aw ) override;" << std::endl;
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
		}

		write() << "};" << std::endl;
		write() << std::endl;
		writeTypedefHandle( servant_name );
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

			if( mt.exceptions.empty() == false )
			{
				write() << "	void exceptionCall( std::size_t _exceptionId, Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;" << std::endl;
			}

			write() << "};" << std::endl;
			write() << std::endl;
			writeTypedefHandle( response_name );
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
		write() << "	" << proxy_name << "( std::size_t _id, const Axe::ProxyAdapterProviderPtr & _adapterProvider );" << std::endl;
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
		m_stream << "#	include <Axe/ProxyAdapterProvider.hpp>" << std::endl;
		m_stream << std::endl;

		Namespace * ns = m_parser->getNamespace();

		generateImplementNamespace( ns );
		generateImplementNamespaceHelper( ns );
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::generateImplementNamespace( Namespace * _namespace )
	{
		m_namespace = _namespace;

		if( _namespace->name.empty() == false )
		{
			write() << "namespace " << _namespace->name << std::endl;
			write() << "{" << std::endl;
			increfTabs();
		}

		const TVectorOrder & order = _namespace->order;

		TVectorStructs & structs = _namespace->structs;
		TVectorClasses & classes = _namespace->classes;
		TVectorExceptions & exceptions = _namespace->exceptions;
		TListNamespaces & namespaces = _namespace->namespaces;

		TVectorStructs::iterator it_struct = structs.begin();
		TVectorClasses::iterator it_class = classes.begin();
		TVectorExceptions::iterator it_exception = exceptions.begin();
		TListNamespaces::iterator it_namespace = namespaces.begin();

		for( TVectorOrder::const_iterator
			it_order = order.begin(),
			it_order_end = order.end();
		it_order != it_order_end;
		++it_order )
		{
			switch( *it_order )
			{
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
					generateImplementNamespace( &*it_namespace );
					++it_namespace;
				}break;
			}
		}

		if( _namespace->name.empty() == false )
		{
			decrefTabs();
			write() << "}" << std::endl;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::generateImplementNamespaceHelper( Declaration::Namespace * _namespace )
	{
		m_namespace = m_namespaceAxe;

		if( _namespace->name.empty() == false )
		{
			write() << "namespace Axe" << std::endl;
			write() << "{" << std::endl;
			increfTabs();
		}

		const TVectorOrder & order = _namespace->order;

		TVectorStructs & structs = _namespace->structs;
		TVectorClasses & classes = _namespace->classes;
		TVectorExceptions & exceptions = _namespace->exceptions;
		TListNamespaces & namespaces = _namespace->namespaces;

		TVectorStructs::iterator it_struct = structs.begin();
		TVectorClasses::iterator it_class = classes.begin();
		TVectorExceptions::iterator it_exception = exceptions.begin();
		TListNamespaces::iterator it_namespace = namespaces.begin();

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
					generateImplementStructHelper( *it_struct );
					++it_struct;
				}break;
			case DECL_CLASS:
				{
					generateImplementClassHelper( *it_class );
					++it_class;
				}break;
			case DECL_NAMESPACE:
				{
					generateImplementNamespaceHelper( &*it_namespace );
					++it_namespace;
				}break;
			}
		}

		if( _namespace->name.empty() == false )
		{
			decrefTabs();
			write() << "}" << std::endl;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::generateImplementStructHelper( const Declaration::Struct & _struct )
	{
		const Struct & st = _struct;

		std::string struct_namespace = writeNamespaceType( st.owner );

		writeLine();
		write() << "void operator << ( Axe::ArchiveInvocation & ar, const " << struct_namespace << st.name << " & _value )" << std::endl;
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
		write() << "void operator >> ( Axe::ArchiveDispatcher & ar, " << struct_namespace << st.name << " & _value )" << std::endl;
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
	void SLAxeGenerator::generateImplementClassHelper( const Declaration::Class & _class )
	{
		const Class & cl = _class;

		for( TVectorMethods::const_iterator
			it_method = cl.methods.begin(),
			it_method_end = cl.methods.end();
		it_method != it_method_end;
		++it_method )
		{
			const Method & mt = *it_method;

			writeLine();

			std::string response_name = writeResponseName( cl.name, mt.name );

			std::string bindResponse = "BindResponse<" + response_name + "Ptr>";

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
		}

		std::string proxy_name = writeProxyName( cl.name );

		writeLine();
		write() << "void operator << ( Axe::ArchiveInvocation & _ar, const " << proxy_name << "Ptr & _value )" << std::endl;
		write() << "{" << std::endl;
		write() << "	_value->write( _ar );" << std::endl;
		write() << "}" << std::endl;
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::generateImplementClass(  const Class & _class )
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

		TVectorBaseClasses bc;
		getBasesClass( cl, bc );

		std::size_t basesMethodCount = 0;

		for( TVectorBaseClasses::iterator
			it_bases_class = bc.begin(),
			it_bases_class_end = bc.end();
		it_bases_class != it_bases_class_end;
		++it_bases_class)
		{
			const Class & cl = **it_bases_class;

			basesMethodCount += cl.methods.size();
		}

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

			std::size_t exceptionId = basesMethodCount + std::distance( cl.methods.begin(), it_method ) + 3;

			write() << "	s_" << servant_name << "_writeException_" << mt.name << "( AxeUtil::nativePtr(m_servant), " << exceptionId << ", ar, _ex );" << std::endl;
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

		TVectorBaseClasses bc;
		getBasesClass( cl, bc );

		std::size_t basesMethodCount = 0;

		for( TVectorBaseClasses::iterator
			it_bases_class = bc.begin(),
			it_bases_class_end = bc.end();
		it_bases_class != it_bases_class_end;
		++it_bases_class)
		{
			const Class & cl = **it_bases_class;

			basesMethodCount += cl.methods.size();
		}

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
				write() << "void s_" << servant_name << "_callMethod_" << mt.name << "( " << servant_name << " * _servant, std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )" << std::endl;
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

			for( TVectorBaseClasses::iterator
				it_bases_class = bc.begin(),
				it_bases_class_end = bc.end();
			it_bases_class != it_bases_class_end;
			++it_bases_class)
			{
				const Class & cl = **it_bases_class;

				if( cl.methods.empty() == false )
				{
					writeLine();
					write() << "void s_" << servant_name << "_subMethod_" << cl.name << "_callMethod( " << servant_name << " * _servant, std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )" << std::endl;
					write() << "{" << std::endl;
					write() << "	static_cast<" << writeServantName(cl.name) << " *>(_servant)->callMethod( _methodId, _requestId, _archive, _session );" << std::endl;
					write() << "}" << std::endl;
				}
			}

			std::string typedef_servant_method = "T" + servant_name + "_callMethod";

			writeLine();
			write() << "typedef void (*" << typedef_servant_method << ")( " << servant_name << " * _servant, std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session );" << std::endl;
			writeLine();
			write() << "static " << typedef_servant_method << " s_" << servant_name << "_callMethods[] =" << std::endl;
			write() << "{" << std::endl;
			write() << "	0" << std::endl;

			for( TVectorBaseClasses::iterator
				it_bases_class = bc.begin(),
				it_bases_class_end = bc.end();
			it_bases_class != it_bases_class_end;
			++it_bases_class)
			{
				const Class & cl = **it_bases_class;

				for( TVectorMethods::const_iterator
					it_method = cl.methods.begin(),
					it_method_end = cl.methods.end();
				it_method != it_method_end;
				++it_method )
				{
					write() << "	, &s_" << servant_name << "_subMethod_" << cl.name << "_callMethod" << std::endl;
				}
			}

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
			write() << "void " << servant_name << "::callMethod( std::size_t _methodId, std::size_t _requestId, Axe::ArchiveDispatcher & _archive, const Axe::SessionPtr & _session )" << std::endl;
			write() << "{" << std::endl;

			//		stream_read * stream = _session->get_streamIn();
			//		switch( _methodId ){

			write() << "	(*s_" << servant_name << "_callMethods[ _methodId ])( this, _methodId, _requestId, _archive, _session );" << std::endl;

			write() << "}" << std::endl;

			for( TVectorBaseClasses::iterator
				it_bases_class = bc.begin(),
				it_bases_class_end = bc.end();
			it_bases_class != it_bases_class_end;
			++it_bases_class)
			{
				const Class & cl = **it_bases_class;

				if( cl.methods.empty() == false )
				{
					write() << "static void s_" << servant_name << "_subMethod_" << cl.name << "_writeException( " << servant_name << " * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )" << std::endl;
					write() << "{" << std::endl;
					write() << "	static_cast<" << writeServantName(cl.name) << " *>( _servant )->writeExceptions_( _methodId, _ar, _ex );" << std::endl;
					write() << "}" << std::endl;
				}
			}

			for( TVectorMethods::const_iterator 
				it_method = cl.methods.begin(), 
				it_method_end = cl.methods.end();
			it_method != it_method_end;
			++it_method	)
			{
				const Method & mt = *it_method;

				writeLine();
				write() << "static void s_" << servant_name << "_writeException_" << mt.name << "( " << servant_name << " * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex )" << std::endl;
				write() << "{" << std::endl;

				if( mt.exceptions.empty() == false )
				{
					write() << "	try" << std::endl;
					write() << "	{" << std::endl;
					write() << "		_ex.rethrow();" << std::endl;
					write() << "	}" << std::endl;

					

					for( TVectorMethodExceptions::const_iterator 
						it_exception = mt.exceptions.begin(),
						it_exception_end = mt.exceptions.end();
					it_exception != it_exception_end;
					++it_exception )
					{
						const MethodException & me = *it_exception;

						write() << "	catch( const " << me.name << " & _ex )" << std::endl;
						write() << "	{" << std::endl;

						std::size_t exceptionId = std::distance( mt.exceptions.begin(), it_exception ) + 100;

						write() << "		_ar.writeSize( " << exceptionId << " );" << std::endl;
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
			write() << "typedef void (*" << typedef_servant_exception << ")( " << servant_name << " * _servant, std::size_t _methodId, Axe::ArchiveInvocation & _ar, const Axe::Exception & _ex );" << std::endl;
			writeLine();
			write() << "static " << typedef_servant_exception << " s_" << servant_name << "_writeExceptions[] =" << std::endl;
			write() << "{" << std::endl;
			write() << "	0" << std::endl;

			for( TVectorBaseClasses::iterator
				it_bases_class = bc.begin(),
				it_bases_class_end = bc.end();
			it_bases_class != it_bases_class_end;
			++it_bases_class)
			{
				const Class & cl = **it_bases_class;

				for( TVectorMethods::const_iterator
					it_method = cl.methods.begin(),
					it_method_end = cl.methods.end();
				it_method != it_method_end;
				++it_method )
				{
					write() << "	, &s_" << servant_name << "_subMethod_" << cl.name << "_writeException" << std::endl;
				}
			}

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

			writeLine();
			write() << "void " << servant_name << "::responseException( std::size_t _methodId, std::size_t _requestId, const Axe::SessionPtr & _session, const Axe::Exception & _ex )" << std::endl;
			write() << "{" << std::endl;
			write() << "	Axe::ArchiveInvocation & aw = _session->beginException( _requestId );" << std::endl;		
			write() << std::endl;
			write() << "	this->writeExceptions_( _methodId, aw, _ex );" << std::endl;
			write() << std::endl;
			write() << "	_session->process();" << std::endl;
			write() << "}" << std::endl;
			writeLine();
			write() << "void " << servant_name << "::writeExceptions_( std::size_t _methodId, Axe::ArchiveInvocation & _aw, const Axe::Exception & _ex )" << std::endl;
			write() << "{" << std::endl;
			write() << "	(*s_" << servant_name << "_writeExceptions[ _methodId ])( this, _methodId, _aw, _ex );" << std::endl;
			write() << "}" << std::endl;
		}

		if( cl.members.empty() == false )
		{
			writeLine();
			write() << "void " << servant_name << "::_restore( Axe::ArchiveDispatcher & _ar )" << std::endl;
			write() << "{" << std::endl;

			for( TVectorMembers::const_iterator
				it = cl.members.begin(),
				it_end = cl.members.end();
			it != it_end;
			++it )
			{
				write() << "	_ar >> " << it->name << ";" << std::endl;
			}

			write() << "}" << std::endl;

			writeLine();
			write() << "void " << servant_name << "::_evict( Axe::ArchiveInvocation & _aw )" << std::endl;
			write() << "{" << std::endl;

			for( TVectorMembers::const_iterator 
				it = cl.members.begin(),
				it_end = cl.members.end();
			it != it_end;
			++it )
			{
				write() << "	_aw << " << it->name << ";" << std::endl;
			}

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

			std::string response_name = writeResponseName( cl.name, mt.name );

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

			if( mt.exceptions.empty() == false )
			{
				writeLine();
				write() << "void " << response_name << "::exceptionCall( std::size_t _exceptionId, Axe::ArchiveDispatcher & _ar, std::size_t _size )" << std::endl;
				write() << "{" << std::endl;
				write() << "	switch( _exceptionId )" << std::endl;
				write() << "	{" << std::endl;

				for( TVectorMethodExceptions::const_iterator
					it_exception = mt.exceptions.begin(),
					it_exception_end = mt.exceptions.end();
				it_exception != it_exception_end;
				++it_exception )
				{
					const MethodException & me = *it_exception;

					std::size_t exceptionEnumerator = std::distance( mt.exceptions.begin(), it_exception ) + 100;

					write() << "	case " << exceptionEnumerator << ":" << std::endl;
					write() << "		{" << std::endl;
					write() << "			" << me.name << " ex;" << std::endl;
					write() << "			ex.read( _ar );" << std::endl;
					write() << "			this->throw_exception( ex ); " << std::endl;
					write() << "		}" << std::endl;
				}

				write() << "	};" << std::endl;
				write() << "}" << std::endl;
			}
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

		TVectorBaseClasses bc;
		getBasesClass( cl, bc );

		std::size_t basesMethodCount = 0;

		for( TVectorBaseClasses::iterator
			it_bases_class = bc.begin(),
			it_bases_class_end = bc.end();
		it_bases_class != it_bases_class_end;
		++it_bases_class)
		{
			const Class & cl = **it_bases_class;

			basesMethodCount += cl.methods.size();
		}

		//write() << std::endl;

		std::string proxy_name = writeProxyName( cl.name );

		writeLine();
		write() << proxy_name << "::" << proxy_name << "( std::size_t _id, const Axe::ProxyAdapterProviderPtr & _adapterProvider )" << std::endl;

		write() << "	: Axe::Proxy(_id, _adapterProvider)" << std::endl;

		for( TVectorParents::const_iterator 
			it_parent = cl.parents.begin(),
			it_parent_end = cl.parents.end();
		it_parent != it_parent_end;
		++it_parent )
		{
			const Parent & pr = *it_parent;

			std::string parent_name = writeProxyName( pr.name );

			write() << "	, " << parent_name << "(_id, _adapterProvider)" << std::endl;
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

			std::size_t methodId = basesMethodCount + std::distance( cl.methods.begin(), it_method ) + 1;
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
	}
	//////////////////////////////////////////////////////////////////////////
	template<class T>
	const T * s_findTypename( Namespace * _namespace, const std::string & _name )
	{
		class FClassName
		{
		public:
			FClassName( const std::string & _name )
				: m_name(_name)
			{
			}

		public:
			bool operator()( const T & _class )
			{
				return m_name == _class.name;
			}

		protected:
			std::string m_name;
		};

		std::vector<T> & v = _namespace->getVector<T>();

		std::vector<T>::iterator it_found = 
			std::find_if( v.begin(), v.end(), FClassName(_name) );

		if( it_found != v.end() )
		{
			return &*it_found;
		}

		for( Namespace::TListNamespaces::iterator
			it = _namespace->namespaces.begin(),
			it_end = _namespace->namespaces.end();
		it != it_end;
		++it )
		{
			const T * t = s_findTypename<T>( &(*it), _name );

			if( t )
			{
				return t;
			}
		}

		return 0;
	}
	//////////////////////////////////////////////////////////////////////////
	template<class T>
	const T * s_findTypename( const TMapParsers & _parsers, const std::string & _name )
	{
		for( TMapParsers::const_iterator
			it = _parsers.begin(),
			it_end = _parsers.end();
		it != it_end;
		++it )
		{
			Declaration::Namespace * ns = it->second->getNamespace();
			const T * t = s_findTypename<T>( ns, _name );

			if( t )
			{
				return t;
			}
		}

		return 0;
	}
	//////////////////////////////////////////////////////////////////////////
	const Declaration::Typedef * SLAxeGenerator::findTypedef( const std::string & _name ) const
	{
		return s_findTypename<Declaration::Typedef>( m_parsers, _name );
	}
	//////////////////////////////////////////////////////////////////////////
	const Declaration::Class * SLAxeGenerator::findClass( const std::string & _name ) const
	{
		return s_findTypename<Declaration::Class>( m_parsers, _name );
	}
	//////////////////////////////////////////////////////////////////////////
	const Declaration::Struct * SLAxeGenerator::findStruct( const std::string & _name ) const
	{
		return s_findTypename<Declaration::Struct>( m_parsers, _name );
	}
	std::string SLAxeGenerator::writeNamespaceType( const Declaration::Namespace * _ns )
	{
		std::string ret = "::";

		while( _ns->name.empty() == false )
		{
			ret = "::" + _ns->name + ret;
			_ns = _ns->parent;
		}

		return ret;
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::getBasesClass( const Declaration::Class & _class, TVectorBaseClasses & _out )
	{
		for( TVectorParents::const_iterator
			it_parent = _class.parents.begin(),
			it_parent_end = _class.parents.end();
		it_parent != it_parent_end;
		++it_parent )
		{
			const Declaration::Class * cs = findClass( it_parent->name );

			if( cs )
			{
				_out.push_back( cs );

				getBasesClass( *cs, _out );
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void SLAxeGenerator::writeTypedefHandle( const std::string & _type )
	{
		write() << "typedef AxeHandle<" << _type << "> " << _type << "Ptr;" << std::endl;
	}
	//////////////////////////////////////////////////////////////////////////
	std::string SLAxeGenerator::writeTypedefName( const std::string & _typedef )
	{
		std::string name = _typedef;

		const Declaration::Typedef * decl = findTypedef( _typedef );

		if( decl->owner != m_namespace )
		{
			std::string nt = writeNamespaceType( decl->owner );
			name = nt + name;
		}

		return name;
	}
	//////////////////////////////////////////////////////////////////////////
	std::string SLAxeGenerator::writeStructName( const std::string & _struct )
	{
		std::string name = _struct;

		const Declaration::Struct * decl = findStruct( _struct );

		if( decl->owner != m_namespace )
		{
			std::string nt = writeNamespaceType( decl->owner );
			name = nt + name;
		}

		return name;
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
		std::string name = "Servant_" + _class;

		const Declaration::Class * decl = findClass( _class );

		if( decl->owner != m_namespace )
		{
			std::string nt = writeNamespaceType( decl->owner );
			name = nt + name;
		}

		return name;
	}
	//////////////////////////////////////////////////////////////////////////
	std::string SLAxeGenerator::writeResponseName( const std::string & _class, const std::string & _method )
	{
		std::string name = "Response_" + _class +"_" + _method;

		const Declaration::Class * decl = findClass( _class );

		if( decl->owner != m_namespace )
		{
			std::string nt = writeNamespaceType( decl->owner );
			name = nt + name;
		}

		return name;	
	}
	//////////////////////////////////////////////////////////////////////////
	std::string SLAxeGenerator::writeProxyName( const std::string & _class )
	{
		if( _class == "Proxy" )
		{
			return "Axe::Proxy";
		}
	
		std::string name = "Proxy_" + _class;

		const Declaration::Class * decl = findClass( _class );

		if( decl->owner != m_namespace )
		{
			std::string nt = writeNamespaceType( decl->owner );
			name = nt + name;
		}

		return name;
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
			else if( _type == "Proxy" )
			{
				return "const Axe::ProxyPtr &";
			}
		}

		const Declaration::Typedef * td = findTypedef( _type );

		if( td )
		{
			std::string ret_type = "const ";
			ret_type += writeTypedefName( _type );
			ret_type += " &";

			return ret_type;
		}

		const Declaration::Struct * st = findStruct( _type );

		if( st )
		{
			std::string ret_type = "const ";
			ret_type += writeStructName(_type);
			ret_type += " &";

			return ret_type;
		}

		const Declaration::Class * cl = findClass( _type );

		if( cl )
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
			else if( _type == "Proxy" )
			{
				return "Axe::ProxyPtr";
			}
		}

		const Declaration::Struct * st = findStruct( _type );

		if( st )
		{
			std::string ret_type = writeStructName(_type);

			return ret_type;
		}

		const Declaration::Class * cl = findClass( _type );

		if( cl )
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

		const Declaration::Class * cl = findClass( _type );

		if( cl )
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
		const Declaration::Class * cl = findClass( _type );

		if( cl )
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
		const Declaration::Class * cl = findClass( _type );

		if( cl )
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
		if( --m_tabs == -1 )
		{
			printf("Bad");
		}
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