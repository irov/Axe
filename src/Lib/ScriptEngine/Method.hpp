#	pragma once

#	include "EmbeddingMethod.hpp"

#	include "Blobject.hpp"

#	include <AxeUtil/Shared.hpp>

namespace AxeScript
{
	class MethodCallback
		: virtual public AxeUtil::Shared
	{
	public:
		virtual void onCallMethod( const std::string & _method, const TBlobject & _properties ) = 0;
	};

	typedef AxeHandle<MethodCallback> MethodCallbackPtr;

	class Method
		: virtual public AxeUtil::Shared
	{
	public:
		Method( const EmbeddingMethodPtr & _embedding, const MethodCallbackPtr & _callback );

	public:
		boost::python::object embedding_call( const boost::python::tuple & _args, const boost::python::dict & _kwds );

	public:
		static void embedding();

	protected:
		EmbeddingMethodPtr m_embedding;
		MethodCallbackPtr m_callback;
	};

	typedef AxeHandle<Method> MethodPtr;
}