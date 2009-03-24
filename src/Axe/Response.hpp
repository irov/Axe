#	pragma once

#	include <AxeUtil/Shared.hpp>

namespace Axe
{
	class ArchiveRead;
	class Exception;

	class Response
		: virtual public AxeUtil::Shared
	{
	public:
		virtual void responseCall( ArchiveRead & _ar, std::size_t _size ) = 0;
		virtual void exceptionCall( ArchiveRead & _ar, std::size_t _size ) = 0;

	protected:
		virtual void throw_exception( const Axe::Exception & _ex ) = 0;

	protected:
		bool exceptionFilter( std::size_t _exceptionId, ArchiveRead & _ar );
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

	typedef boost::function<void (const Exception &)> TBindNullException;

	TBindNullException noneExceptionFilter();

	template<class R, class E>
	BindHelperResponse<R, E> bindResponse( const R & _response, const E & _exception )
	{
		return BindHelperResponse<R, E>( _response, _exception );
	}
}