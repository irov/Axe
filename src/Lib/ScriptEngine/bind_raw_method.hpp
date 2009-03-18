#	pragma once

#	include <boost/python/raw_function.hpp>
#	include <boost/python/slice.hpp>
#	include <boost/function_types/parameter_types.hpp>

//////////////////////////////////////////////////////////////////////////
template<class F>
static boost::python::object bind_raw_method_adapter( F f, const boost::python::tuple & _args, const boost::python::dict & _kwds )
{
	typedef typename boost::function_types::parameter_types<F>::type mpl_parameter_type;
	typedef typename boost::mpl::front<mpl_parameter_type>::type class_type_ref;
	typedef typename boost::remove_reference<class_type_ref>::type class_type;

	boost::python::object self = _args[0];

	class_type * cl = boost::python::extract<class_type *>( self );

	boost::python::tuple true_args( 
		_args[ boost::python::slice( 1, boost::python::_ ) ]
	);

	return boost::bind( f, cl, _1, _2 )( true_args, _kwds );
}
//////////////////////////////////////////////////////////////////////////
template<class F>
void bind_raw_method_i( boost::python::objects::class_base & _class, const char * _name, F f )
{
	boost::python::objects::add_to_namespace(
		_class
		, _name
		, boost::python::detail::make_raw_function(
		boost::python::objects::py_function(
		boost::python::detail::raw_dispatcher<F>(f)
		, boost::mpl::vector1<PyObject*>()
		, 0
		, (std::numeric_limits<unsigned>::max)()
		)
		)
		, boost::python::detail::def_helper<char const*>(0).doc()
		);
}

template<class F>
void bind_raw_method( boost::python::objects::class_base & _class, const char * _name, F f )
{
	bind_raw_method_i( _class, _name, boost::bind( &bind_raw_method_adapter<F>, f, _1, _2 ) );
}