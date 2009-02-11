#	pragma once

#	include <boost/intrusive_ptr.hpp>

namespace Axe
{
	class Shared
	{
	public:
		Shared()
			: m_refcount(0)
		{
		}

		virtual ~Shared()
		{
		}

	public:
		friend inline void intrusive_ptr_add_ref( Shared * p )
		{
			++p->m_refcount;
		}

		friend inline void intrusive_ptr_release( Shared * p )
		{
			if( --p->m_refcount == 0 )
			{
				delete p;
			}
		}

	protected:
		std::size_t m_refcount;
	};

	#	define AxeHandle boost::intrusive_ptr

	template<class T, class Y>
	inline T handleCast( const AxeHandle<Y> & _handle )
	{
		Y * y = _handle.get();
		T ptr = static_cast<typename T::element_type *>(y);

		return ptr;
	}
}