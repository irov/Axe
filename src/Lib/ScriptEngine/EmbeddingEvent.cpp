#	include "EmbeddingEvent.hpp"

EmbeddingEvent::EmbeddingEvent( const std::string & _name, const boost::python::tuple & _args )
: m_name(_name)
, m_args(_args)
{
}

const std::string & EmbeddingEvent::getName() const
{
	return m_name;
}

const boost::python::tuple & EmbeddingEvent::getArgs() const
{
	return m_args;
}
