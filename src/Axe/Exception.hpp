#	pragma once

#	include <exception>

namespace Axe
{
	class ArchiveInvocation;
	class ArchiveDispatcher;

	class Exception
		: public std::exception
	{
	public:
		virtual void rethrow() const = 0;

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

	public:
		void write( ArchiveInvocation & _aw ) const;
		void read( ArchiveDispatcher & _ar );

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
	};

	class UnknownException
		: public Exception
	{
	public:
		void rethrow() const override;

	public:
		void write( ArchiveInvocation & _ar ) const;
		void read( ArchiveDispatcher & _ar );
	};

	class CriticalException
		: public LocalException
	{
	public:
		CriticalException( const std::string & _message );

	public:
		void rethrow() const override;
	};
}