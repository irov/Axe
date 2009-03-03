#	pragma once

#	include "Shared.hpp"

namespace Axe
{
	class ArchiveRead;

	class Response
		: virtual public Shared
	{
	public:
		virtual void responseCall( ArchiveRead & _ar ) = 0;
		virtual void exceptionCall( ArchiveRead & _ar ) = 0;
	};
}