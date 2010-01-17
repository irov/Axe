#	include "pch.hpp"

#	include <Axe/Response.hpp>

#	include <Axe/ArchiveDispatcher.hpp>

#	include <Axe/Exception.hpp>
#	include <Axe/DispatcherException.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	void Response::exceptionCall( std::size_t _exceptionId, ArchiveDispatcher & _ar, std::size_t _size )
	{
		//Empty
	}
	//////////////////////////////////////////////////////////////////////////
	bool Response::dispatch( ArchiveDispatcher & _ar, std::size_t _size )
	{
		bool successful;
		_ar.read( successful );

		if( successful )
		{
			this->responseCall( _ar, _size );
			return true;
		}

		std::size_t exceptionId;
		_ar.readSize( exceptionId );

		if( exceptionId == DispatcherServantRelocateException::exceptionId )
		{
			DispatcherServantRelocateException ex;
			ex.read( _ar );

			const ConnectionCachePtr & connectionCache = _ar.getConnectionCache();

			connectionCache->relocateProxy( ex.servantId, ex.adapterId );

			return false; //wait next response
		}

		try
		{
			readExceptionFilter( exceptionId, _ar );

			this->exceptionCall( exceptionId, _ar, _size );
		}
		catch( const Exception & _ex )
		{
			this->throw_exception( _ex );
		}

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