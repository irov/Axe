#	pragma once

#	include <AxeUtil/Shared.hpp>

namespace Axe
{
	class ArchiveDispatcher;
	class Exception;

	class Response
		: virtual public AxeUtil::Shared
	{
	public:
		virtual void responseCall( ArchiveDispatcher & _ar, std::size_t _size ) = 0;
		virtual void exceptionCall( std::size_t _exceptionId, ArchiveDispatcher & _ar, std::size_t _size );

	public:
		bool dispatch( ArchiveDispatcher & _ar, std::size_t _size );

	protected:
		virtual void throw_exception( const Exception & _ex ) = 0;
	};

	template<class F>
	class BindResponse;

	template<class F, class R>
	class BindResponseHelper
		: public F
	{
	protected:
		typedef boost::function<R> TBindResponse;
		typedef boost::function<void(const Axe::Exception &)> TBindException;
	
	public:
		BindResponseHelper( const TBindResponse & _response, const TBindException & _exception )
			: m_response(_response)
			, m_exception(_exception)
		{
		}

	public:
		void throw_exception( const Axe::Exception & _ex ) override
		{
			m_exception(_ex);
		}

	protected:
		TBindResponse m_response;
		TBindException m_exception;
	};

	template<class R, class E>
	class BindResponseAdapter
	{
	public:
		BindResponseAdapter( const R & _response, const E & _exception )
			: m_response(_response)
			, m_exception(_exception)
		{
		}

	public:
		template<class F>
		operator F ()
		{
			return new BindResponse<F>( m_response, m_exception );
		}

	protected:
		const R & m_response;
		const E & m_exception;
	};

	template<class F, class E>
	class BindResponseAdapterFunction
	{
	public:
		BindResponseAdapterFunction( const F & _function, const E & _exception )
			: m_function(_function)
			, m_exception(_exception)
		{
		}

	public:
		template<class F>
		operator F ()
		{
			return new BindResponse<F>( boost::bind( m_function, _1 ), m_exception );
		}

	protected:
		F m_function;
		const E & m_exception;
	};

	template<class M, class C, class E>
	class BindResponseAdapterMethod
	{
	public:
		BindResponseAdapterMethod( C * _self, M _method, const E & _exception )
			: m_self(_self)
			, m_method(_method)
			, m_exception(_exception)
		{
		}

	public:
		template<class F>
		operator F ()
		{
			return new BindResponse<F>( boost::bind( m_method, handlePtr(m_self), _1 ), m_exception );
		}

	protected:
		C * m_self;
		M m_method;		
		const E & m_exception;
	};

	template<class C>
	class BindResponseAdapterChain
	{
	public:
		BindResponseAdapterChain( const AxeHandle<C> & _cb )
			: m_cb(_cb)
		{
		}

	public:
		template<class F>
		operator F () const
		{
			return new BindResponse<F>( 
				boost::bind( &C::response, m_cb )
				, boost::bind( &C::throw_exception, m_cb, _1 )
				);
		}

	protected:
		AxeHandle<C> m_cb;
	};

	typedef boost::function<void (const Exception &)> TBindNullException;

	TBindNullException noneExceptionFilter();

	class BindResponseAdapterEmpty
	{
	public:
		template<class F>
		operator F ()
		{
			return new BindResponse<F>( boost::bind( &empty ) , noneExceptionFilter() );
		}

	protected:
		static void empty()
		{
			//Empty
		}
	};

	template<class R, class E>
	BindResponseAdapter<R, E> bindResponse( const R & _response, const E & _exception )
	{
		return BindResponseAdapter<R, E>( _response, _exception );
	}

	template<class R>
	BindResponseAdapter<R, TBindNullException> bindResponse( const R & _response )
	{
		return bindResponse( _response, noneExceptionFilter() );
	}

	static BindResponseAdapterEmpty bindResponseEmpty()
	{
		return BindResponseAdapterEmpty();
	}

	template<class M, class C, class E>
	BindResponseAdapterMethod<M,C,E> bindResponseMethod(  C * _self, const M & _method, const E & _exception )
	{
		return BindResponseAdapterMethod<M,C,E>( _self, _method, _exception );
	}

	template<class M, class C>
	BindResponseAdapterMethod<M,C,TBindNullException> bindResponseMethod( C * _self, const M & _method )
	{
		return bindResponseMethod( _self, _method, noneExceptionFilter() );
	}

	template<class F, class E>
	BindResponseAdapterFunction<F,E> bindResponseFunction(  const F & _function, const E & _exception )
	{
		return BindResponseAdapterFunction<F,E>( _function, _exception );
	}

	template<class F>
	BindResponseAdapterFunction<F,TBindNullException> bindResponseFunction( const F & _function )
	{
		return bindResponseFunction( _function, noneExceptionFilter() );
	}

	template<class C>
	BindResponseAdapterChain<C> bindResponseChain(  const AxeHandle<C> & _cb )
	{
		return BindResponseAdapterChain<C>( _cb );
	}
}