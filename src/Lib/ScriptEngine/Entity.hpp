#	pragma once

#	include "Blobject.hpp"

#	include "EmbeddingEntity.hpp"
#	include "EmbeddingProperty.hpp"

#	include "Method.hpp"

namespace AxeScript
{
	class EntityListener
		: virtual public AxeUtil::Shared
	{
	public:
		virtual void onCallEntityMethod( const std::string & _entity, const std::string & _method, const TBlobject & _blobject ) = 0;		
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
		void add_attr( const std::string & _name, const boost::python::object & _obj );
		void add_method( const std::string & _name, const MethodPtr & _embedding );

	public:
		void onCallMethod( const std::string & _method, const TBlobject & _properties ) override;

	public:
		static void embedding();

	protected:
		std::size_t m_revision;

		std::string m_name;

		EmbeddingEntityPtr m_embedding;
		EntityListenerPtr m_listener;

		typedef std::map<std::string, MethodPtr> TMapMethods;
		TMapMethods m_methods;

		struct Member
		{
			std::size_t revision;
			EmbeddingPropertyPtr embeddingProperty;
			boost::python::object value;
		};

		typedef std::map<std::string, Member> TMapProtocolMembers;
		TMapProtocolMembers m_protocolMembers;

		typedef std::map<std::string, boost::python::object> TMapNativeMembers;
		TMapNativeMembers m_nativeMembers;
	};

	typedef AxeHandle<Entity> EntityPtr;
}