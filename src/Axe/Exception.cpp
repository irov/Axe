#	include "pch.hpp"

#	include <exception>

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
	std::size_t LocalException::getId() const
	{
		return 1;
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
	std::size_t StdException::getId() const
	{
		return 2;
	}
	//////////////////////////////////////////////////////////////////////////
	void UnknownException::rethrow() const
	{
		throw *this;
	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t UnknownException::getId() const
	{
		return 3;
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
	std::size_t CriticalException::getId() const
	{
		return 4;
	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t ProtocolException::getId() const
	{
		return 100;
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
			::Axe::LocalException rex;
			_ar.writeSize( rex.getId() );
			rex.write( _ar );
		}
		catch( const std::exception & _ex )
		{
			const char * ch_what = _ex.what();
			std::string message = ( ch_what )?ch_what:std::string();
			::Axe::StdException rex( message );
			_ar.writeSize( rex.getId() );
			rex.write( _ar );
		}
		catch( ... )
		{
			::Axe::UnknownException rex;
			_ar.writeSize( rex.getId() );
			rex.write( _ar );
		}
	}
}