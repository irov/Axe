#	include "pch.hpp"

#	include <Axe/Exception.hpp>

#	include <Axe/ArchiveInvocation.hpp>
#	include <Axe/ArchiveDispatcher.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	LocalException::LocalException()
	{
	}
	//////////////////////////////////////////////////////////////////////////
	LocalException::LocalException( const std::string & _message )
		: m_message(_message)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void LocalException::rethrow() const
	{
		throw *this;
	}
	//////////////////////////////////////////////////////////////////////////
	void LocalException::write( ArchiveInvocation & _aw ) const
	{
		_aw << m_message;
	}
	//////////////////////////////////////////////////////////////////////////
	void LocalException::read( ArchiveDispatcher & _ar )
	{
		_ar >> m_message;
	}
	//////////////////////////////////////////////////////////////////////////
	StdException::StdException( const std::string & _message )
		: LocalException(_message)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void StdException::rethrow() const
	{
		throw *this;
	}
	//////////////////////////////////////////////////////////////////////////
	void UnknownException::rethrow() const
	{
		throw *this;
	}
	//////////////////////////////////////////////////////////////////////////
	void UnknownException::write( ArchiveInvocation & _ar ) const
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void UnknownException::read( ArchiveDispatcher & _ar )
	{
	}
	//////////////////////////////////////////////////////////////////////////
	CriticalException::CriticalException( const std::string & _message )
		: LocalException(_message)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void CriticalException::rethrow() const
	{
		throw *this;
	}
	//////////////////////////////////////////////////////////////////////////
	void writeExceptionFilter( ArchiveInvocation & _ar )
	{
		try
		{
			throw;
		}
		catch( const ::Axe::Exception & _ex )
		{
			const char * ch_what = _ex.what();
			std::string message = ( ch_what )?ch_what:std::string();
			::Axe::LocalException lex( message );
			_ar.writeSize( 1 );
			lex.write( _ar );
		}
		catch( const std::exception & _ex )
		{
			const char * ch_what = _ex.what();
			std::string message = ( ch_what )?ch_what:std::string();
			::Axe::StdException lex( message );
			_ar.writeSize( 2 );
			lex.write( _ar );
		}
		catch( ... )
		{
			::Axe::UnknownException uex;
			_ar.writeSize(0);
			uex.write( _ar );
		}
	}
}