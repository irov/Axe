#	include "pch.hpp"

#	include "EmbeddingProperty.hpp"

namespace AxeScript
{
	void EmbeddingProperty::embedding( const std::string & _name )
	{
		boost::python::class_<EmbeddingProperty, boost::noncopyable>( _name.c_str(), boost::python::no_init )
			;
	}
}