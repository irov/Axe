#	pragma once

#	include "Entity.hpp"
#	include "EmbeddingEntity.hpp"
#	include "EmbeddingProperty.hpp"

#	include <boost/python/raw_function.hpp>
#	include <boost/bind.hpp>

class Protocol
{
	typedef boost::python::object ( TRawFunction )( const boost::python::tuple & _args, const boost::python::dict & _kw );

public:
	void embedding()
	{
		boost::python::detail::init_module( "Protocol", &init_module_protocol );
		m_module = boost::python::import( "Protocol" );

		boost::python::scope sc( m_module );
		
		boost::function< TRawFunction > def_class_func = boost::bind( &Protocol::def_class, this, _1, _2 );
		boost::python::object def_class_obj = boost::python::raw_function( def_class_func );
		boost::python::setattr( m_module, "def_class", def_class_obj );

		boost::function< TRawFunction > create_class_func = boost::bind( &Protocol::create_class, this, _1, _2 );
		boost::python::object create_class_obj = boost::python::raw_function( create_class_func );
		boost::python::setattr( m_module, "create_class", create_class_obj );

		Entity::embedding();
		EmbeddingEntity::embedding();
		EmbeddingProperty::embedding("Property");

		boost::python::setattr( m_module, "Bool", EmbeddingPropertyTemplate<bool>::embedding("PropertyBool") );
		boost::python::setattr( m_module, "Int", EmbeddingPropertyTemplate<int>::embedding("PropertyInt") );
		boost::python::setattr( m_module, "Float", EmbeddingPropertyTemplate<float>::embedding("PropertyFloat") );
	}

public:
	boost::python::object def_class( const boost::python::tuple & _args, const boost::python::dict & _kw )
	{
		std::string moduleName = boost::python::extract<std::string>( _args[0] );

		boost::python::object obj_module = boost::python::import( moduleName.c_str() );
		boost::python::object obj_type = boost::python::getattr( obj_module, moduleName.c_str() );

		EmbeddingEntity * ec = new EmbeddingEntity( obj_type );

		m_embeddingEntities.insert( std::make_pair( moduleName, ec ) );

		return boost::python::object( boost::ref( ec ) );
	}

	boost::python::object create_class( const boost::python::tuple & _args, const boost::python::dict & _kw )
	{	
		std::string entityName = boost::python::extract<std::string>( _args[0] );
		std::string moduleName = boost::python::extract<std::string>( _args[1] );

		TMapEmbeddingEntities::iterator it_found = m_embeddingEntities.find( moduleName );

		if( it_found == m_embeddingEntities.end() )
		{
			return boost::python::object();
		}

		EmbeddingEntity * embedding = it_found->second;

		const boost::python::object & type = embedding->getType();

		boost::python::object obj = type();

		Entity * en = boost::python::extract<Entity *>(obj);

		en->initialize( entityName, embedding, 0 );

		for( TMapEmbeddingProperties::const_iterator 
			it = embedding->get_properties_begin(),
			it_end = embedding->get_properties_end();
		it != it_end;
		++it )
		{
			const std::string & key = it->first;

			boost::python::object none;
			en->add_attr( key, none );
		}

		for( TMapEmbeddingMethods::const_iterator 
			it = embedding->get_methods_begin(),
			it_end = embedding->get_methods_end();
		it != it_end;
		++it )
		{
			const std::string & key = it->first;
			EmbeddingMethod * embedding = it->second;

			Method * mt = new Method( embedding, en );

			en->add_method( key, mt );
		}

		return obj;
	}

protected:
	static void init_module_protocol()
	{
	}

protected:
	boost::python::object m_module;

	typedef std::map<std::string, EmbeddingEntity *> TMapEmbeddingEntities;
	TMapEmbeddingEntities m_embeddingEntities;
};