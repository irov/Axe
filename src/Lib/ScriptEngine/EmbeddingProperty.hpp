#	pragma once

#	include <AxeUtil/Shared.hpp>

#	include "Blobject.hpp"

#	include <vector>

namespace AxeScript
{
	class EmbeddingProperty
		: virtual public AxeUtil::Shared
	{
	public:
		static void embedding( const std::string & _name );

	public:
		virtual void write( TBlobject & _blob, const boost::python::object & _obj ) = 0;
	};

	typedef AxeHandle<EmbeddingProperty> EmbeddingPropertyPtr;

	template<class T>
	class EmbeddingPropertyTemplate
		: public EmbeddingProperty
	{
	public:
		static boost::python::object embedding( const std::string & _name )
		{
			boost::python::class_<EmbeddingPropertyTemplate<T>, boost::python::bases<EmbeddingProperty> >( _name.c_str(), boost::python::no_init )
				;

			EmbeddingPropertyTemplate<T> * propertyTemplate = new EmbeddingPropertyTemplate<T>();
			boost::python::object obj( boost::ref(propertyTemplate) );

			return obj;		
		}

	public:
		void write( TBlobject & _blob, const boost::python::object & _obj ) override
		{
			T value = boost::python::extract<T>(_obj);

			write_blob( _blob, &value, &value + 1 );
		}

		void write_blob( TBlobject & _blob, void * _begin, void * _end )
		{
			_blob.insert( _blob.end()
				, (TBlobject::value_type*)_begin
				, (TBlobject::value_type*)_end 
				);
		}
	};
}