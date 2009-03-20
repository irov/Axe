#	pragma once

#	include <Axe/Shared.hpp>

namespace Axe
{
	class ArchiveRead;

	class Response
		: virtual public Shared
	{
	public:
		virtual void responseCall( ArchiveRead & _ar, std::size_t _size ) = 0;
		virtual void exceptionCall( ArchiveRead & _ar, std::size_t _size ) = 0;
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

	template<class R, class E>
	BindHelperResponse<R, E> bindResponse( const R & _response, const E & _exception )
	{
		return BindHelperResponse<R, E>( _response, _exception );
	}
}