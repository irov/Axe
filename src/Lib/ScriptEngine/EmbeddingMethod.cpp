#	include "pch.hpp"
#	include "EmbeddingMethod.hpp"

namespace AxeScript
{
	//////////////////////////////////////////////////////////////////////////
	EmbeddingMethod::EmbeddingMethod( const std::string & _name, const boost::python::tuple & _args )
		: m_name(_name)
		, m_args(_args)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	const std::string & EmbeddingMethod::getName() const
	{
		return m_name;
	}
	//////////////////////////////////////////////////////////////////////////
	const boost::python::tuple & EmbeddingMethod::getArgs() const
	{
		return m_args;
	}
}