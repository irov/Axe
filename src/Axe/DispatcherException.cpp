#	include "pch.hpp"

#	include <Axe/DispatcherException.hpp>

#	include <Axe/ArchiveInvocation.hpp>
#	include <Axe/ArchiveDispatcher.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	void DispatcherServantRelocateException::rethrow() const
	{
		throw *this;
	}
	//////////////////////////////////////////////////////////////////////////
	void DispatcherServantRelocateException::write( ArchiveInvocation & _ar ) const
	{
		_ar << servantId;
		_ar << adapterId;
	}
	//////////////////////////////////////////////////////////////////////////
	void DispatcherServantRelocateException::read( ArchiveDispatcher & _ar )
	{
		_ar >> servantId;
		_ar >> adapterId;
	}
	//////////////////////////////////////////////////////////////////////////
	void DispatcherServantNotFoundException::rethrow() const
	{
		throw *this;
	}
	//////////////////////////////////////////////////////////////////////////
	void DispatcherServantNotFoundException::write( ArchiveInvocation & _ar ) const
	{
		_ar << servantId;
		_ar << adapterId;
	}
	//////////////////////////////////////////////////////////////////////////
	void DispatcherServantNotFoundException::read( ArchiveDispatcher & _ar )
	{
		_ar >> servantId;
		_ar >> adapterId;
	}
	//////////////////////////////////////////////////////////////////////////

}