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
		friend inline void intrusive_ptr_add_ref( const Shared * p )
		{
			p->incref();
		}

		friend inline void intrusive_ptr_release( const Shared * p )
		{
			p->decref();
		}

	private:
		void incref() const
		{
			++m_refcount;
		}

		void decref() const
		{
			if( m_refcount == 0 )
			{
				delete this;
			}
		}

	protected:
		mutable std::size_t m_refcount;
	};

	#	define AxeHandle boost::intrusive_ptr

	template<class T, class Y>
	inline T handleCast( const AxeHandle<Y> & _handle )
	{
		typedef typename T::element_type element_type;
		return boost::dynamic_pointer_cast<element_type>( _handle );
	}
}