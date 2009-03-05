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
		virtual void write( ArchiveWrite & _ar ) const = 0;
		virtual void read( ArchiveRead & _ar ) = 0;
	};

	class LocalException
		: public Exception
	{
	public:
		LocalException( const std::string & _message );

	public:
		void write( ArchiveWrite & _aw ) const;
		void read( ArchiveRead & _ar );

	protected:
		std::string m_message;
	};

	class UnknownException
		: public Exception
	{
	public:
		void write( ArchiveWrite & _ar ) const;
		void read( ArchiveRead & _ar );
	};
}