#	include "pch.hpp"

#	include "MethodAdapter.hpp"

#	include "PythonBindRawMethod.hpp"

namespace AxeScript
{
	//////////////////////////////////////////////////////////////////////////
	MethodAdapter::MethodAdapter( const MethodCallbackPtr & _callback )
		: m_callback(_callback)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void MethodAdapter::makeMethod( const std::string & _name, const EmbeddingMethodPtr & _embedding )
	{
		MethodPtr md = new Method( _embedding, m_callback );

		m_methods.insert( std::make_pair( _name, md ) );
	}
	//////////////////////////////////////////////////////////////////////////
	boost::python::object MethodAdapter::embedding_setattr( const boost::python::tuple & _args, const boost::python::dict & _kwds )
	{
		return boost::python::object(0);
	}
	//////////////////////////////////////////////////////////////////////////
	boost::python::object MethodAdapter::embedding_getattr( const boost::python::tuple & _args, const boost::python::dict & _kwds )
	{
		std::string key = boost::python::extract<std::string>(_args[0]);

		TMapMethods::iterator it_method_found = m_methods.find( key );

		if( it_method_found == m_methods.end() )
		{
			return boost::python::object();
		}

		const MethodPtr & mt = it_method_found->second;
		boost::python::object obj( mt );
		return obj;	
	}
	//////////////////////////////////////////////////////////////////////////
	boost::python::object MethodAdapter::embedding_hasattr( const boost::python::tuple & _args, const boost::python::dict & _kwds )
	{
		std::string key = boost::python::extract<std::string>(_args[0]);

		TMapMethods::iterator it_method_found = m_methods.find( key );

		if( it_method_found == m_methods.end() )
		{
			return boost::python::object( false );
		}

		return boost::python::object( true );
	}
	//////////////////////////////////////////////////////////////////////////
	void MethodAdapter::embedding()
	{
		boost::python::class_<MethodAdapter, boost::noncopyable> en("MethodAdapter", boost::python::no_init)
			;

		boost_ext::python::bind_raw_method( en, "__setattr__", &MethodAdapter::embedding_setattr);
		boost_ext::python::bind_raw_method( en, "__getattr__", &MethodAdapter::embedding_getattr);
		boost_ext::python::bind_raw_method( en, "__hasattr__", &MethodAdapter::embedding_hasattr);
	}
}