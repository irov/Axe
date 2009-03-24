#	pragma once

#	include <AxeUtil/Shared.hpp>

#	include <string>

namespace AxeScript
{
	class EmbeddingEvent
		: virtual public AxeUtil::Shared
	{
	public:
		EmbeddingEvent( const std::string & _name, const boost::python::tuple & _args );

	public:
		const std::string & getName() const;
		const boost::python::tuple & getArgs() const;

	protected:
		std::string m_name;
		boost::python::tuple m_args;
	};

	typedef AxeHandle<EmbeddingEvent> EmbeddingEventPtr;
}