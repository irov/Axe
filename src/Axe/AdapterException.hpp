#	pragma once

#	include <Axe/Exception.hpp>

namespace Axe
{
	class AdapterException
		: public Exception
	{

	};

	class AdapterServantAlreadyExistException
		: public AdapterException
	{
	public:
		void rethrow() const override;

	public:
		void write( ArchiveInvocation & _ar ) const override;
		void read( ArchiveDispatcher & _ar ) override;

	public:
		static const std::size_t exceptionId = 11;

	public:
		std::size_t servantId;
		std::size_t adapterId;
	};
}