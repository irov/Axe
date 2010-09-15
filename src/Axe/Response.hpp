#	pragma once

#	include <AxeUtil/Shared.hpp>

#	include <Axe/Exception.hpp>
#	include <Axe/AxeCallback.hpp>

namespace Axe
{
	class ArchiveDispatcher;

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
}