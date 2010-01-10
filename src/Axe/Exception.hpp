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
		virtual std::size_t getId() const = 0;

	public:
		virtual void write( ArchiveInvocation & _ar ) const = 0;
		virtual void read( ArchiveDispatcher & _ar ) = 0;		
	};

	class LocalException
		: public Exception
	{
	public:
		LocalException();
		LocalException( const std::string & _message );

	public:
		void rethrow() const override;
		std::size_t getId() const override;

	public:
		void write( ArchiveInvocation & _aw ) const override;
		void read( ArchiveDispatcher & _ar ) override;

	protected:
		std::string m_message;
	};

	class StdException
		: public LocalException
	{
	public:
		StdException( const std::string & _message );

	public:
		void rethrow() const override;
		std::size_t getId() const override;
	};

	class UnknownException
		: public Exception
	{
	public:
		void rethrow() const override;
		std::size_t getId() const override;

	public:
		void write( ArchiveInvocation & _ar ) const override;
		void read( ArchiveDispatcher & _ar ) override;
	};

	class CriticalException
		: public LocalException
	{
	public:
		CriticalException( const std::string & _message );

	public:
		void rethrow() const override;
		std::size_t getId() const override;
	};

	class ProtocolException
		: public Exception
	{
	public:
		std::size_t getId() const override;
	};

	void writeExceptionFilter( ArchiveInvocation & _ar );
}