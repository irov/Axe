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

	public:
		void write( ArchiveInvocation & _ar ) const override;
		void read( ArchiveDispatcher & _ar ) override;

	public:
		static const std::size_t exceptionId = 10;

	public:
		std::size_t servantId;
		std::size_t adapterId;
	};

	class DispatcherObjectNotFoundException
		: public DispatcherException
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