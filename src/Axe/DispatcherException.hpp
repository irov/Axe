#	pragma once

#	include <Axe/Exception.hpp>

namespace Axe
{
	class DispatcherException
		: public Exception
	{
		
	};

	class DispatcherServantRelocateException
		: public DispatcherException
	{
	public:
		void rethrow() const override;
		std::size_t getId() const override;

	public:
		void write( ArchiveInvocation & _ar ) const override;
		void read( ArchiveDispatcher & _ar ) override;

	public:
		std::size_t servantId;
		std::size_t hostId;
	};
}