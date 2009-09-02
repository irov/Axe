#	pragma once

#	include <AxeUtil/Archive.hpp>
#	include <AxeUtil/Shared.hpp>

#	include "EmbeddingMethod.hpp"
#	include "EmbeddingEvent.hpp"
#	include "EmbeddingProperty.hpp"

#	include <boost/python.hpp>

#	include <map>
#	include <vector>
#	include <string>

namespace AxeScript
{
	typedef AxeHandle<class Entity> EntityPtr;
	typedef AxeHandle<class EntityListener> EntityListenerPtr;

	class EmbeddingEntity
		: virtual public AxeUtil::Shared
	{
	public:
		EmbeddingEntity( const boost::python::object & _type );

	public:
		const boost::python::object & getType() const;

	public:
		static void embedding();

	public:
		void def_method( const std::string & _name, const boost::python::tuple & _args );
		void def_event( const std::string & _name, const boost::python::tuple & _args );
		void def_property( const std::string & _name, const boost::python::object & _type );

	public:
		EntityPtr createEntity( const std::string & _entityName, const EntityListenerPtr & _listener );

	protected:	
		boost::python::object m_type;

		typedef std::map<std::string, EmbeddingMethodPtr> TMapEmbeddingMethods;
		TMapEmbeddingMethods m_methods;

		typedef std::map<std::string, EmbeddingEventPtr> TMapEmbeddingEvents;
		TMapEmbeddingEvents m_events;

		typedef std::map<std::string, EmbeddingPropertyPtr> TMapEmbeddingProperties;
		TMapEmbeddingProperties m_properties;
	};

	typedef AxeHandle<EmbeddingEntity> EmbeddingEntityPtr;
}