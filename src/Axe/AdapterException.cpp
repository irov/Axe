#	include "pch.hpp"

#	include "AdapterException.hpp"

#	include <Axe/ArchiveInvocation.hpp>
#	include <Axe/ArchiveDispatcher.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	void AdapterServantAlreadyExistException::rethrow() const
	{
		throw *this;
	}
	//////////////////////////////////////////////////////////////////////////
	void AdapterServantAlreadyExistException::write( ArchiveInvocation & _ar ) const
	{
		_ar << servantId;
		_ar << adapterId;
	}
	//////////////////////////////////////////////////////////////////////////
	void AdapterServantAlreadyExistException::read( ArchiveDispatcher & _ar )
	{
		_ar >> servantId;
		_ar >> adapterId;
	}
	//////////////////////////////////////////////////////////////////////////
	void AdapterServantFactoryNotRegistredGeneratorException::rethrow() const
	{
		throw *this;
	}
	//////////////////////////////////////////////////////////////////////////
	void AdapterServantFactoryNotRegistredGeneratorException::write( ArchiveInvocation & _ar ) const
	{
		_ar << servantType;
		_ar << adapterId;
	}
	//////////////////////////////////////////////////////////////////////////
	void AdapterServantFactoryNotRegistredGeneratorException::read( ArchiveDispatcher & _ar )
	{
		_ar >> servantType;
		_ar >> adapterId;
	}
	//////////////////////////////////////////////////////////////////////////
	void AdapterNotRegistredException::rethrow() const
	{
		throw *this;
	}
	//////////////////////////////////////////////////////////////////////////
	void AdapterNotRegistredException::write( ArchiveInvocation & _ar ) const
	{
		_ar << adapterName;
	}
	//////////////////////////////////////////////////////////////////////////
	void AdapterNotRegistredException::read( ArchiveDispatcher & _ar )
	{
		_ar >> adapterName;
	}
}