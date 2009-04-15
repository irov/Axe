#	include "pch.hpp"

#	include <Axe/Response.hpp>
#	include <Axe/Exception.hpp>

namespace Axe
{
	bool Response::exceptionFilter( std::size_t _exceptionId, ArchiveDispatcher & _ar )
	{
		switch( _exceptionId )
		{
		case 0:
			{
				Axe::UnknownException ex;
				ex.read( _ar );
				this->throw_exception( ex );
			}break;
		case 1:
			{
				Axe::LocalException ex;
				ex.read( _ar );
				this->throw_exception( ex );
			}break;
		default:
			return false;
		};

		return true;
	}
	//////////////////////////////////////////////////////////////////////////
	static void nullExceptionFilter( const Exception & )
	{

	}
	//////////////////////////////////////////////////////////////////////////
	TBindNullException noneExceptionFilter()
	{
		return boost::bind( &nullExceptionFilter, _1 );
	}

}