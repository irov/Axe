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
	std::size_t DispatcherServantRelocateException::getId() const
	{
		return 10;
	}
	//////////////////////////////////////////////////////////////////////////
	void DispatcherServantRelocateException::write( ArchiveInvocation & _ar ) const
	{
		_ar << servantId;
		_ar << hostId;
	}
	//////////////////////////////////////////////////////////////////////////
	void DispatcherServantRelocateException::read( ArchiveDispatcher & _ar )
	{
		_ar >> servantId;
		_ar >> hostId;
	}
	//////////////////////////////////////////////////////////////////////////
	void DispatcherObjectNotFoundException::rethrow() const
	{
		throw *this;
	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t DispatcherObjectNotFoundException::getId() const
	{
		return 11;
	}
	//////////////////////////////////////////////////////////////////////////
	void DispatcherObjectNotFoundException::write( ArchiveInvocation & _ar ) const
	{
		_ar << servantId;
		_ar << hostId;
	}
	//////////////////////////////////////////////////////////////////////////
	void DispatcherObjectNotFoundException::read( ArchiveDispatcher & _ar )
	{
		_ar >> servantId;
		_ar >> hostId;
	}
	//////////////////////////////////////////////////////////////////////////

}