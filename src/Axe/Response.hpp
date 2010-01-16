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

	template<class M, class C, class E>
	class BindHelperMethodResponse
	{
	public:
		BindHelperMethodResponse( const M & _method, C * _self, const E & _exception )
			: m_method(_method)
			, m_self(_self)
			, m_exception(_exception)
		{
		}

	public:
		template<class F>
		operator F ()
		{
			return new BindResponse<F>( boost::bind( m_method, handlePtr(m_self), _1 ) , m_exception );
		}

	protected:
		const M & m_method;
		C * m_self;
		const E & m_exception;
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
	BindHelperMethodResponse<M,C,E> bindResponseMethod( const M & _method, C * _self, const E & _exception )
	{
		return BindHelperMethodResponse<M,C,E>( _method, _self, _exception );
	}

	template<class M, class C>
	BindHelperMethodResponse<M,C,TBindNullException> bindResponseMethod( const M & _method, C * _self )
	{
		return bindResponseMethod( _method, _self, noneExceptionFilter() );
	}
}