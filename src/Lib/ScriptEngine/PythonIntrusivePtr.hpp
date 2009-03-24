// Based on boost header: shared_ptr_from_python.hpp.
#	pragma once

#	include <IceUtil/Shared.h>
#	include <IceUtil/Handle.h>

//namespace boost 
//{ 
//	namespace python
//	{
//		template<class T> inline T * get_pointer(IceUtil::Handle<T> const & p)
//		{
//			return p.get();
//		}
//	}
//
//	template<class T> inline T * get_pointer(IceUtil::Handle<T> const & p)
//	{
//		return p.get();
//	}
//}
//
//namespace Carbon
//{
//	namespace Property
//	{
//        template<class T> inline T * get_pointer(IceUtil::Handle<T> const & p)
//        {
//            return p.get();
//        }
//	}
//}

namespace IceUtil
{
    template<class T> inline T * get_pointer(IceUtil::Handle<T> const & p)
    {
        return p.get();
    }
}

namespace boost_ext
{
	namespace python
	{
		using namespace boost;
		using namespace boost::python;
		using namespace boost::python::converter;

		template <class T>
		struct intrusive_ptr_from_python
		{
			intrusive_ptr_from_python()
			{
				converter::registry::insert(&convertible, &construct, 
					type_id<IceUtil::Handle<T> >());
			}

		private:
			static void* convertible(PyObject* p)
			{
				if (p == Py_None)
					return p;

				return converter::get_lvalue_from_python(p, 
					registered<T>::converters);
			}

			static void construct(PyObject* source, 
				rvalue_from_python_stage1_data* data)
			{
				void* const storage = 
					((converter::rvalue_from_python_storage<IceUtil::Handle<T> 
					>*)data)->storage.bytes;
				// Deal with the "None" case.
				if (data->convertible == source)
					new (storage) IceUtil::Handle<T>();
				else
					new (storage) IceUtil::Handle<T>(
					static_cast<T*>(data->convertible)
					);

				data->convertible = storage;
			}
		};

		template <class T, class Bases>
		inline void register_intrusive_ptr_from_python_and_casts(T*, Bases)
		{
			using namespace boost::python::objects;

			// Constructor performs registration
			boost::python::detail::force_instantiate(intrusive_ptr_from_python<T>());

			//
			// register all up/downcasts here.  We're using the alternate
			// interface to mpl::for_each to avoid an MSVC 6 bug.
			//
			register_dynamic_id<T>();
			mpl::for_each(register_base_of<T>(), (Bases*)0, 
				(boost::add_pointer<mpl::_>*)0);
		};

		class register_intrusive
		{
		public:
			template<class T>
			register_intrusive( const T & _class )
				: m_class(_class)
			{
				typedef typename T::wrapped_type wrapped_type;
				typedef typename T::metadata metadata;

				register_intrusive_ptr_from_python_and_casts( 
					(wrapped_type *)0
					, typename metadata::bases()
					);
			}

		public:
			const boost::python::object & getClass()
			{
				return m_class;
			}

		protected:
			boost::python::object m_class;
		};
	}
}
