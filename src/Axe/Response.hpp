#	pragma once

#	include "Shared.hpp"

namespace Axe
{
	class ArchiveRead;

	class Response
		: public Shared
	{
	public:
		virtual void responseCall( ArchiveRead & _ar ) = 0;
	};
}