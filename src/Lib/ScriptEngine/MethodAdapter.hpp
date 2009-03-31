#	pragma once

#	include "Method.hpp"

#	include <AxeUtil/Shared.hpp>

#	include <map>
#	include <string>

namespace AxeScript
{
	class MethodAdapter
		: virtual public AxeUtil::Shared
	{
	public:
		MethodAdapter( const MethodCallbackPtr & _callback );

	public:
		void makeMethod( const std::string & _name, const EmbeddingMethodPtr & _embedding );

	public:
		boost::python::object embedding_setattr( const boost::python::tuple & _args, const boost::python::dict & _kwds );
		boost::python::object embedding_getattr( const boost::python::tuple & _args, const boost::python::dict & _kwds );
		boost::python::object embedding_hasattr( const boost::python::tuple & _args, const boost::python::dict & _kwds );
	
	public:
		static void embedding();

	protected:
		MethodCallbackPtr m_callback;

		typedef std::map<std::string, MethodPtr> TMapMethods;
		TMapMethods m_methods;
	};

	typedef AxeHandle<MethodAdapter> MethodAdapterPtr;
}