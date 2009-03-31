#	include "pch.hpp"
#	include "Method.hpp"

#	include "EmbeddingProperty.hpp"

#	include "PythonBindRawMethod.hpp"

namespace AxeScript
{
	//////////////////////////////////////////////////////////////////////////
	Method::Method( const EmbeddingMethodPtr & _embedding, const MethodCallbackPtr & _callback )
		: m_embedding(_embedding)
		, m_callback(_callback)
	{

	}
	//////////////////////////////////////////////////////////////////////////
	boost::python::object Method::embedding_call( const boost::python::tuple & _args, const boost::python::dict & _kwds )
	{
		const std::string & name = m_embedding->getName();
		const boost::python::tuple & argsType = m_embedding->getArgs();

		boost::python::ssize_t argsType_len = boost::python::len( argsType );

		TBlobject blobject; 

		for( boost::python::ssize_t 
			it = 0,
			it_end = argsType_len;
		it != it_end;
		++it )
		{
			boost::python::object pytype = argsType[ it ];

			EmbeddingPropertyPtr ep = boost::python::extract<EmbeddingPropertyPtr>(pytype);

			boost::python::object obj = _args[ it ];

			ep->write( blobject, obj );
		}

		m_callback->onCallMethod( name, blobject );

		return boost::python::object();
	}
	//////////////////////////////////////////////////////////////////////////
	void Method::embedding()
	{
		boost::python::class_<Method, boost::noncopyable> mt("Method", boost::python::no_init )
			;

		boost_ext::python::bind_raw_method( mt, "__call__", &Method::embedding_call );
	}
}