#	include "Entity.hpp"

#	include "bind_raw_method.hpp"

//////////////////////////////////////////////////////////////////////////
Method::Method( EmbeddingMethod * _embedding, MethodCallback * _callback )
	: m_embedding(_embedding)
	, m_callback(_callback)
{

}
//////////////////////////////////////////////////////////////////////////
boost::python::object Method::embedding_call( const boost::python::tuple & _args, const boost::python::dict & _kwds )
{
	const std::string & name = m_embedding->getName();
	const boost::python::tuple & args = m_embedding->getArgs();

	boost::python::ssize_t args_len = boost::python::len( args );

	TBlobject blobject; 

	for( boost::python::ssize_t 
		it = 0,
		it_end = args_len;
	it != it_end;
	++it )
	{
		boost::python::object pytype = args[ it ];
		
		EmbeddingProperty * ep = boost::python::extract<EmbeddingProperty *>(pytype);

		boost::python::object obj = _args[ it ];

		ep->write( blobject, obj );
	}

	m_callback->onCallMethod( name, blobject );

	return boost::python::object();
}
//////////////////////////////////////////////////////////////////////////
Entity::Entity()
	: m_revision(0)
	, m_embedding(0)
	, m_listener(0)
{
}
//////////////////////////////////////////////////////////////////////////
void Entity::initialize( const std::string & _name, EmbeddingEntity * _embedding, EntityListener * _listener )
{
	m_name = _name;
	m_embedding = _embedding;
	m_listener = _listener;
}
//////////////////////////////////////////////////////////////////////////
void Entity::add_attr( const std::string & _name, const boost::python::object & _obj  )
{
	Member mb;
	mb.revision = 0;
	mb.value = _obj;
	m_protocolMembers.insert( std::make_pair( _name, mb ) );
}
//////////////////////////////////////////////////////////////////////////
void Entity::add_method( const std::string & _name, Method * _method )
{
	m_methods.insert( std::make_pair( _name, _method ) );
}
//////////////////////////////////////////////////////////////////////////
boost::python::object Entity::embedding_setattr( const boost::python::tuple & _args, const boost::python::dict & _kwds )
{
	std::string name = boost::python::extract<std::string>(_args[0]);
	boost::python::object obj = _args[1];

	TMapProtocolMembers::iterator it_found = m_protocolMembers.find( name );

	if( it_found == m_protocolMembers.end() )
	{
		m_nativeMembers[ name ] = obj;

		return boost::python::object(1);
	}

	Member & mb = it_found->second;

	mb.revision = ++m_revision;
	mb.value = obj;

	return boost::python::object(1);
}
//////////////////////////////////////////////////////////////////////////
boost::python::object Entity::embedding_getattr( const boost::python::tuple & _args, const boost::python::dict & _kwds )
{
	std::string key = boost::python::extract<std::string>(_args[0]);

	TMapProtocolMembers::iterator it_protocol_found = m_protocolMembers.find( key );

	if( it_protocol_found != m_protocolMembers.end() )
	{
		return it_protocol_found->second.value;
	}

	TMapMethods::iterator it_method_found = m_methods.find( key );

	if( it_method_found != m_methods.end() )
	{
		Method * mt = it_method_found->second;
		boost::python::object obj( boost::ref(mt) );
		return obj;
	}

	TMapNativeMembers::iterator it_native_found = m_nativeMembers.find( key );

	if( it_native_found != m_nativeMembers.end() )
	{
		return it_native_found->second;
	}
	
	return boost::python::object();
}
//////////////////////////////////////////////////////////////////////////
boost::python::object Entity::embedding_hasattr( const boost::python::tuple & _args, const boost::python::dict & _kwds )
{
	std::string key = boost::python::extract<std::string>(_args[0]);

	TMapProtocolMembers::iterator it_protocol_found = m_protocolMembers.find( key );

	if( it_protocol_found != m_protocolMembers.end() )
	{
		return boost::python::object( true );
	}

	TMapMethods::iterator it_method_found = m_methods.find( key );

	if( it_method_found != m_methods.end() )
	{
		return boost::python::object( true );
	}
	
	TMapNativeMembers::iterator it_native_found = m_nativeMembers.find( key );

	if( it_native_found != m_nativeMembers.end() )
	{
		return boost::python::object( true );
	}

	return boost::python::object( false );
}
//////////////////////////////////////////////////////////////////////////
void Entity::onCallMethod( const std::string & _method, const TBlobject & _args )
{
	TMapMethods::iterator it_found = m_methods.find( _method );

	if( it_found == m_methods.end() )
	{
		return;
	}
	
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

	bind_raw_method( en, "__setattr__", &Entity::embedding_setattr);
	bind_raw_method( en, "__getattr__", &Entity::embedding_getattr);
	bind_raw_method( en, "__hasattr__", &Entity::embedding_hasattr);

	boost::python::class_<Method, boost::noncopyable> mt("Method", boost::python::no_init )
		;

	bind_raw_method( mt, "__call__", &Method::embedding_call );
}