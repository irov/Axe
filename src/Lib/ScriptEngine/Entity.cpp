#	include "pch.hpp"

#	include "Entity.hpp"

#	include "PythonBindRawMethod.hpp"

namespace AxeScript
{
	//////////////////////////////////////////////////////////////////////////
	Entity::Entity()
		: m_revision(0)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Entity::initialize( const std::string & _name, const EmbeddingEntityPtr & _embedding, const EntityListenerPtr & _listener )
	{
		m_name = _name;
		m_embedding = _embedding;
		m_listener = _listener;
	}
	//////////////////////////////////////////////////////////////////////////
	void Entity::addProperty( const std::string & _name, const PropertyPtr & _property )
	{
		m_properties.insert( std::make_pair( _name, _property ) );
	}
	//////////////////////////////////////////////////////////////////////////
	void Entity::addMethodAdapter( const std::string & _name, const MethodAdapterPtr & _methodAdapter )
	{
		m_methodAdapters.insert( std::make_pair( _name, _methodAdapter ) );
	}
	//////////////////////////////////////////////////////////////////////////
	boost::python::object Entity::embedding_setattr( const boost::python::tuple & _args, const boost::python::dict & _kwds )
	{
		std::string name = boost::python::extract<std::string>(_args[0]);
		boost::python::object obj = _args[1];

		TMapProperties::iterator it_found = m_properties.find( name );

		if( it_found == m_properties.end() )
		{
			m_members[ name ] = obj;

			return boost::python::object(1);
		}

		it_found->second->update( obj );

		return boost::python::object(1);
	}
	//////////////////////////////////////////////////////////////////////////
	boost::python::object Entity::embedding_getattr( const boost::python::tuple & _args, const boost::python::dict & _kwds )
	{
		std::string key = boost::python::extract<std::string>(_args[0]);

		TMapProperties::iterator it_protocol_found = m_properties.find( key );

		if( it_protocol_found != m_properties.end() )
		{
			const PropertyPtr & property = it_protocol_found->second;

			return property->getValue();
		}

		TMapMethodAdapters::iterator it_method_found = m_methodAdapters.find( key );

		if( it_method_found != m_methodAdapters.end() )
		{
			const MethodAdapterPtr & mt = it_method_found->second;
			boost::python::object obj( mt );
			return obj;
		}

		TMapMembers::iterator it_native_found = m_members.find( key );

		if( it_native_found != m_members.end() )
		{
			return it_native_found->second;
		}

		return boost::python::object();
	}
	//////////////////////////////////////////////////////////////////////////
	boost::python::object Entity::embedding_hasattr( const boost::python::tuple & _args, const boost::python::dict & _kwds )
	{
		std::string key = boost::python::extract<std::string>(_args[0]);

		TMapProperties::iterator it_protocol_found = m_properties.find( key );

		if( it_protocol_found != m_properties.end() )
		{
			return boost::python::object( true );
		}

		TMapMethodAdapters::iterator it_method_found = m_methodAdapters.find( key );

		if( it_method_found != m_methodAdapters.end() )
		{
			return boost::python::object( true );
		}

		TMapMembers::iterator it_native_found = m_members.find( key );

		if( it_native_found != m_members.end() )
		{
			return boost::python::object( true );
		}

		return boost::python::object( false );
	}
	//////////////////////////////////////////////////////////////////////////
	void Entity::onCallMethod( const std::string & _method, const TBlobject & _args )
	{
		if( m_listener )
		{
			m_listener->onCallEntityMethod( m_name, _method, _args );
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void Entity::embedding()
	{
		boost::python::class_<Entity> en("Entity", boost::python::init<>())
			;

		boost_ext::python::bind_raw_method( en, "__setattr__", &Entity::embedding_setattr);
		boost_ext::python::bind_raw_method( en, "__getattr__", &Entity::embedding_getattr);
		boost_ext::python::bind_raw_method( en, "__hasattr__", &Entity::embedding_hasattr);
	}
}
