#	pragma once

#	include "EmbeddingEntity.hpp"
#	include "EmbeddingProperty.hpp"

#	include "MethodAdapter.hpp"
#	include "Property.hpp"

namespace AxeScript
{
	class EntityListener
		: virtual public AxeUtil::Shared
	{
	public:
		virtual void onCallEntityMethod( const std::string & _entity, const std::string & _method, const AxeUtil::Archive & _blobject ) = 0;		
	};

	typedef AxeHandle<EntityListener> EntityListenerPtr;

	class Entity
		: virtual public AxeUtil::Shared
		, public MethodCallback
	{
	public:
		Entity();

	public:
		void initialize( const std::string & _name, const EmbeddingEntityPtr & _embedding, const EntityListenerPtr & _listener );

	public:
		boost::python::object embedding_setattr( const boost::python::tuple & _args, const boost::python::dict & _kwds );
		boost::python::object embedding_getattr( const boost::python::tuple & _args, const boost::python::dict & _kwds );
		boost::python::object embedding_hasattr( const boost::python::tuple & _args, const boost::python::dict & _kwds );

	public:
		void addProperty( const std::string & _name, const PropertyPtr & _obj );
		void addMethodAdapter( const std::string & _name, const MethodAdapterPtr & _obj );
				
	public:
		void onCallMethod( const std::string & _method, const AxeUtil::Archive & _properties ) override;

	public:
		static void embedding();

	protected:
		std::size_t m_revision;

		std::string m_name;

		EmbeddingEntityPtr m_embedding;
		EntityListenerPtr m_listener;

		typedef std::map<std::string, PropertyPtr> TMapProperties;
		TMapProperties m_properties;

		typedef std::map<std::string, MethodAdapterPtr> TMapMethodAdapters;
		TMapMethodAdapters m_methodAdapters;

		typedef std::map<std::string, boost::python::object> TMapMembers;
		TMapMembers m_members;
	};

	typedef AxeHandle<Entity> EntityPtr;
}