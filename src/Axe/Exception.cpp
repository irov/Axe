#	include "pch.hpp"

#	include <exception>

#	include <Axe/Exception.hpp>

#	include <Axe/ArchiveInvocation.hpp>
#	include <Axe/ArchiveDispatcher.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	void EmptyException::write( ArchiveInvocation & _ar ) const
	{
		//Empty
	}
	//////////////////////////////////////////////////////////////////////////
	void EmptyException::read( ArchiveDispatcher & _ar )
	{
		//Empty
	}
	//////////////////////////////////////////////////////////////////////////
	void InternalException::rethrow() const
	{
		throw *this;
	}
	//////////////////////////////////////////////////////////////////////////
	void InternalException::write( ArchiveInvocation & _aw ) const
	{
		//Empty
	}
	//////////////////////////////////////////////////////////////////////////
	void InternalException::read( ArchiveDispatcher & _ar )
	{
		//Empty
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
	void CriticalException::rethrow() const
	{
		throw *this;
	}
	//////////////////////////////////////////////////////////////////////////
	void ProtocolMismatchException::rethrow() const
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
			InternalException rex;
			_ar.writeSize( InternalException::exceptionId );
			rex.write( _ar );
		}
		catch( const std::exception & _ex )
		{
			const char * ch_what = _ex.what();

			StdException rex;
			rex.message = ( ch_what )?ch_what:std::string();
			
			_ar.writeSize( StdException::exceptionId );
			rex.write( _ar );
		}
		catch( ... )
		{
			UnknownException rex;
			_ar.writeSize( UnknownException::exceptionId );
			rex.write( _ar );
		}
	}
	//////////////////////////////////////////////////////////////////////////
	bool readExceptionFilter( std::size_t _exceptionId, ArchiveDispatcher & _ar )
	{

#	define AXE_CASE_EXCEPTION( D_Exception )\
		case D_Exception::exceptionId:\
		{\
			D_Exception ex;\
			ex.read( _ar );\
			throw ex;\
		}break

		switch( _exceptionId )
		{
			AXE_CASE_EXCEPTION(InternalException);
			AXE_CASE_EXCEPTION(StdException);
			AXE_CASE_EXCEPTION(UnknownException);
		default:
			return false;
		};

#	undef AXE_CASE_EXCEPTION

		return true;
	}
}