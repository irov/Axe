#	pragma once

#	include "Blobject.hpp"

#	include "EmbeddingMethod.hpp"
#	include "EmbeddingEvent.hpp"
#	include "EmbeddingProperty.hpp"

#	include <boost/python.hpp>

#	include <map>
#	include <vector>
#	include <string>

typedef std::map<std::string, EmbeddingMethod *> TMapEmbeddingMethods;
typedef std::map<std::string, EmbeddingEvent *> TMapEmbeddingEvents;
typedef std::map<std::string, EmbeddingProperty *> TMapEmbeddingProperties;

class EmbeddingEntity
{
public:
	EmbeddingEntity( const boost::python::object & _type );

public:
	static void embedding();

public:
	void def_method( const std::string & _name, const boost::python::tuple & _args );
	void def_event( const std::string & _name, const boost::python::tuple & _args );
	void def_property( const std::string & _name, const boost::python::object & _type );

public:
	TMapEmbeddingMethods::const_iterator get_methods_begin() const;
	TMapEmbeddingMethods::const_iterator get_methods_end() const;
	TMapEmbeddingProperties::const_iterator get_properties_begin() const;
	TMapEmbeddingProperties::const_iterator get_properties_end() const;

public:
	const boost::python::object & getType() const;

protected:	
	boost::python::object m_type;
	TMapEmbeddingMethods m_embeddingMethods;
	TMapEmbeddingEvents m_embeddingEvents;
	TMapEmbeddingProperties m_embeddingProperties;
};