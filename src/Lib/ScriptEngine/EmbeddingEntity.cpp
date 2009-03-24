#	include "pch.hpp"

#	include "EmbeddingEntity.hpp"
#	include "Entity.hpp"

namespace AxeScript
{
	//////////////////////////////////////////////////////////////////////////
	EmbeddingEntity::EmbeddingEntity( const boost::python::object & _type )
		: m_type(_type)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void EmbeddingEntity::embedding()
	{
		boost::python::class_<EmbeddingEntity, boost::noncopyable>("EmbeddingClass", boost::python::no_init )
			.def("def_method", &EmbeddingEntity::def_method )
			.def("def_event", &EmbeddingEntity::def_event )
			.def("def_property", &EmbeddingEntity::def_property )
			;
	}
	//////////////////////////////////////////////////////////////////////////
	void EmbeddingEntity::def_method( const std::string & _name, const boost::python::tuple & _args )
	{
		m_methods.insert( std::make_pair(_name, new EmbeddingMethod( _name, _args )) );
	}
	//////////////////////////////////////////////////////////////////////////
	void EmbeddingEntity::def_event( const std::string & _name, const boost::python::tuple & _args )
	{
		m_events.insert( std::make_pair(_name, new EmbeddingEvent( _name, _args )) );
	}
	//////////////////////////////////////////////////////////////////////////
	void EmbeddingEntity::def_property( const std::string & _name, const boost::python::object & _type )
	{
		EmbeddingProperty * property = boost::python::extract<EmbeddingProperty *>(_type);
		m_properties.insert( std::make_pair(_name, property) );
	}
	//////////////////////////////////////////////////////////////////////////
	const boost::python::object & EmbeddingEntity::getType() const
	{
		return m_type;
	}
	//////////////////////////////////////////////////////////////////////////
	EntityPtr EmbeddingEntity::createEntity( const std::string & _entityName, const EntityListenerPtr & _listener )
	{
		boost::python::object obj = m_type();

		EntityPtr en = boost::python::extract<EntityPtr>(obj);

		en->initialize( _entityName, this, _listener );

		for( TMapEmbeddingProperties::const_iterator 
			it = m_properties.begin(),
			it_end = m_properties.end();
		it != it_end;
		++it )
		{
			const std::string & key = it->first;

			boost::python::object none;
			en->add_attr( key, none );
		}

		for( TMapEmbeddingMethods::const_iterator 
			it = m_methods.begin(),
			it_end = m_methods.end();
		it != it_end;
		++it )
		{
			const std::string & key = it->first;
			const EmbeddingMethodPtr & embedding = it->second;

			MethodPtr mt = new Method( embedding, en );

			en->add_method( key, mt );
		}

		return en;
	}
}