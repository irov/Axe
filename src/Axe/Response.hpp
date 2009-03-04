#	pragma once

#	include "Shared.hpp"

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
}