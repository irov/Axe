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

	template<class R, class E>
	class BindHelperResponse
	{
	public:
		BindHelperResponse( const R & _response, const E & _exception )
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
	class BindHelperResponseFunction
	{
	public:
		BindHelperResponseFunction( const F & _function, const E & _exception )
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
	class BindHelperResponseMethod
	{
	public:
		BindHelperResponseMethod( C * _self, M _method, const E & _exception )
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
	class BindHelperResponseChain
	{
	public:
		BindHelperResponseChain( const AxeHandle<C> & _cb )
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

	class BindHelperEmptyResponse
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
	BindHelperResponse<R, E> bindResponse( const R & _response, const E & _exception )
	{
		return BindHelperResponse<R, E>( _response, _exception );
	}

	template<class R>
	BindHelperResponse<R, TBindNullException> bindResponse( const R & _response )
	{
		return bindResponse( _response, noneExceptionFilter() );
	}

	static BindHelperEmptyResponse bindResponseEmpty()
	{
		return BindHelperEmptyResponse();
	}

	template<class M, class C, class E>
	BindHelperResponseMethod<M,C,E> bindResponseMethod(  C * _self, const M & _method, const E & _exception )
	{
		return BindHelperResponseMethod<M,C,E>( _self, _method, _exception );
	}

	template<class M, class C>
	BindHelperResponseMethod<M,C,TBindNullException> bindResponseMethod( C * _self, const M & _method )
	{
		return bindResponseMethod( _self, _method, noneExceptionFilter() );
	}

	template<class F, class E>
	BindHelperResponseFunction<F,E> bindResponseFunction(  const F & _function, const E & _exception )
	{
		return BindHelperResponseFunction<F,E>( _function, _exception );
	}

	template<class F>
	BindHelperResponseFunction<F,TBindNullException> bindResponseFunction( const F & _function )
	{
		return bindResponseFunction( _function, noneExceptionFilter() );
	}

	template<class C>
	BindHelperResponseChain<C> bindResponseChain(  const AxeHandle<C> & _cb )
	{
		return BindHelperResponseChain<C>( _cb );
	}
}