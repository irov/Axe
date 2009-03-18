#	include "EmbeddingEntity.hpp"

EmbeddingEntity::EmbeddingEntity( const boost::python::object & _type )
: m_type(_type)
{
}

void EmbeddingEntity::embedding()
{
	boost::python::class_<EmbeddingEntity, boost::noncopyable>("EmbeddingClass", boost::python::no_init )
		.def("def_method", &EmbeddingEntity::def_method )
		.def("def_event", &EmbeddingEntity::def_event )
		.def("def_property", &EmbeddingEntity::def_property )
		;
}

void EmbeddingEntity::def_method( const std::string & _name, const boost::python::tuple & _args )
{
	m_embeddingMethods.insert( std::make_pair(_name, new EmbeddingMethod( _name, _args )) );
}

void EmbeddingEntity::def_event( const std::string & _name, const boost::python::tuple & _args )
{
	m_embeddingEvents.insert( std::make_pair(_name, new EmbeddingEvent( _name, _args )) );
}

void EmbeddingEntity::def_property( const std::string & _name, const boost::python::object & _type )
{
	EmbeddingProperty * property = boost::python::extract<EmbeddingProperty *>(_type);
	m_embeddingProperties.insert( std::make_pair(_name, property) );
}

TMapEmbeddingMethods::const_iterator EmbeddingEntity::get_methods_begin() const
{
	return m_embeddingMethods.begin();
}

TMapEmbeddingMethods::const_iterator EmbeddingEntity::get_methods_end() const
{
	return m_embeddingMethods.end();
}

TMapEmbeddingProperties::const_iterator EmbeddingEntity::get_properties_begin() const
{
	return m_embeddingProperties.begin();
}

TMapEmbeddingProperties::const_iterator EmbeddingEntity::get_properties_end() const
{
	return m_embeddingProperties.end();
}

const boost::python::object & EmbeddingEntity::getType() const
{
	return m_type;
}