#	pragma once

#	include <string>

namespace Axe
{
	class ArchiveInvocation;
	class ArchiveDispatcher;

	class Exception
	{
	public:
		virtual void rethrow() const = 0;

	public:
		virtual void write( ArchiveInvocation & _ar ) const = 0;
		virtual void read( ArchiveDispatcher & _ar ) = 0;
	};

	class EmptyException
		: public Exception
	{
	public:
		void write( ArchiveInvocation & _ar ) const override;
		void read( ArchiveDispatcher & _ar ) override;
	};

	class LocalException
		: public Exception
	{
	public:
		void rethrow() const override;

	public:
		void write( ArchiveInvocation & _aw ) const override;
		void read( ArchiveDispatcher & _ar ) override;

	public:
		static const std::size_t exceptionId = 1;

	public:
		std::string message;
	};

	class StdException
		: public LocalException
	{
	public:
		void rethrow() const override;

	public:
		static const std::size_t exceptionId = 2;
	};

	class UnknownException
		: public EmptyException
	{
	public:
		void rethrow() const override;

	public:
		static const std::size_t exceptionId = 3;
	};

	class CriticalException
		: public EmptyException
	{
	public:
		void rethrow() const override;

	public:
		static const std::size_t exceptionId = 4;
	};

	class ProtocolMismatchException
		: public EmptyException
	{
	public:
		void rethrow() const override;

	public:
		static const std::size_t exceptionId = 5;
	};

	class ProtocolCallException
		: public Exception
	{
	};

	void writeExceptionFilter( ArchiveInvocation & _ar );
	bool readExceptionFilter( std::size_t _exceptionId, ArchiveDispatcher & _ar );
}