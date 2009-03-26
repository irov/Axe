#	pragma once

#	include <exception>

namespace Axe
{
	class ArchiveWrite;
	class ArchiveRead;

	class Exception
		: public std::exception
	{
	public:
		virtual void rethrow() const = 0;

	public:
		virtual void write( ArchiveWrite & _ar ) const = 0;
		virtual void read( ArchiveRead & _ar ) = 0;
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
		void write( ArchiveWrite & _aw ) const;
		void read( ArchiveRead & _ar );

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
		void write( ArchiveWrite & _ar ) const;
		void read( ArchiveRead & _ar );
	};
}