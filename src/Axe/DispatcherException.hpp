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
		static const std::size_t exceptionId = EX_DispatcherServantRelocateException;

	public:
		std::size_t servantId;
		std::size_t adapterId;
	};

	class DispatcherServantNotFoundException
		: public DispatcherException
	{
	public:
		void rethrow() const override;

	public:
		void write( ArchiveInvocation & _ar ) const override;
		void read( ArchiveDispatcher & _ar ) override;

	public:
		static const std::size_t exceptionId = EX_DispatcherServantNotFoundException;

	public:
		std::size_t servantId;
		std::size_t adapterId;
	};

	class DispatcherUniqueNotFoundException
		: public DispatcherException
	{
	public:
		void rethrow() const override;

	public:
		void write( ArchiveInvocation & _ar ) const override;
		void read( ArchiveDispatcher & _ar ) override;

	public:
		static const std::size_t exceptionId = EX_DispatcherUniqueNotFoundException;

	public:
		std::string uniqueId;
		std::size_t adapterId;
	};
}