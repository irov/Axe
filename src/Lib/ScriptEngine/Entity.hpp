#	pragma once

#	include "Blobject.hpp"

#	include "EmbeddingEntity.hpp"

#	include <boost/python.hpp>

#	include <map>
#	include <vector>
#	include <string>

#	include <stdio.h>

class EmbeddingProperty;

typedef std::vector<EmbeddingProperty *> TVectorEmbeddingProperties;

class MethodCallback
{
public:
	virtual void onCallMethod( const std::string & _method, const TBlobject & _properties ) = 0;
};

class Method
{
public:
	Method( EmbeddingMethod * _embedding, MethodCallback * _callback );

public:
	boost::python::object embedding_call( const boost::python::tuple & _args, const boost::python::dict & _kwds );

protected:
	EmbeddingMethod * m_embedding;
	MethodCallback * m_callback;
};

class EntityListener
{
public:
	virtual void onCallEntityMethod( const std::string & _entity, const std::string & _method, const TBlobject & _blobject ) = 0;		
};

class Entity
	: public MethodCallback
{
public:
	Entity();

public:
	void initialize( const std::string & _name, EmbeddingEntity * _embedding, EntityListener * _listener );

public:
	boost::python::object embedding_setattr( const boost::python::tuple & _args, const boost::python::dict & _kwds );
	boost::python::object embedding_getattr( const boost::python::tuple & _args, const boost::python::dict & _kwds );
	boost::python::object embedding_hasattr( const boost::python::tuple & _args, const boost::python::dict & _kwds );

public:
	void add_attr( const std::string & _name, const boost::python::object & _obj );
	void add_method( const std::string & _name, Method * _embedding );

public:
	void onCallMethod( const std::string & _method, const TBlobject & _properties ) override;

public:
	static void embedding();

protected:
	std::size_t m_revision;

	std::string m_name;

	EmbeddingEntity * m_embedding;
	EntityListener * m_listener;

	typedef std::map<std::string, Method *> TMapMethods;
	TMapMethods m_methods;

	struct Member
	{
		std::size_t revision;
		EmbeddingProperty * embeddingProperty;
		boost::python::object value;
	};

	typedef std::map<std::string, Member> TMapProtocolMembers;
	TMapProtocolMembers m_protocolMembers;

	typedef std::map<std::string, boost::python::object> TMapNativeMembers;
	TMapNativeMembers m_nativeMembers;
};
