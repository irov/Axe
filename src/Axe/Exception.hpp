#	pragma once

#	include <exception>

#	include "Shared.hpp"

namespace Axe
{
	class ArchiveWrite;
	class ArchiveRead;

	class Exception
		: virtual public Shared
		, public std::exception
	{
	public:
		virtual void write( ArchiveWrite & _ar ) = 0;
		virtual void read( ArchiveRead & _ar ) = 0;
	};

	typedef AxeHandle<Exception> ExceptionPtr;
}