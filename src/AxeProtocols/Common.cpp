#	include "pch.hpp"

#	include "Common.hpp"

#	include <Axe/ArchiveInvocation.hpp>
#	include <Axe/ArchiveDispatcher.hpp>
#	include <Axe/ProxyAdapterProvider.hpp>

namespace AxeProtocol
{
}
namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & ar, const ::AxeProtocol::Direction & _value )
	{
		ar << _value.x;
		ar << _value.y;
		ar << _value.z;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator >> ( Axe::ArchiveDispatcher & ar, ::AxeProtocol::Direction & _value )
	{
		ar >> _value.x;
		ar >> _value.y;
		ar >> _value.z;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & ar, const ::AxeProtocol::Position & _value )
	{
		ar << _value.x;
		ar << _value.y;
		ar << _value.z;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator >> ( Axe::ArchiveDispatcher & ar, ::AxeProtocol::Position & _value )
	{
		ar >> _value.x;
		ar >> _value.y;
		ar >> _value.z;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & ar, const ::AxeProtocol::Pivot & _value )
	{
		ar << _value.pos;
		ar << _value.dir;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator >> ( Axe::ArchiveDispatcher & ar, ::AxeProtocol::Pivot & _value )
	{
		ar >> _value.pos;
		ar >> _value.dir;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & ar, const ::AxeProtocol::MoveDesc & _value )
	{
		ar << _value.pos;
		ar << _value.dir;
		ar << _value.timeStamp;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator >> ( Axe::ArchiveDispatcher & ar, ::AxeProtocol::MoveDesc & _value )
	{
		ar >> _value.pos;
		ar >> _value.dir;
		ar >> _value.timeStamp;
	}
}
