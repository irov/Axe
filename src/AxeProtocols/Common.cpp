#	include "pch.hpp"

#	include "Common.hpp"

#	include <Axe/ArchiveInvocation.hpp>
#	include <Axe/ArchiveDispatcher.hpp>
#	include <Axe/ProxyHostProvider.hpp>

namespace AxeProtocol
{
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & ar, const Direction & _value )
	{
		ar << _value.x;
		ar << _value.y;
		ar << _value.z;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator >> ( Axe::ArchiveDispatcher & ar, Direction & _value )
	{
		ar >> _value.x;
		ar >> _value.y;
		ar >> _value.z;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & ar, const Position & _value )
	{
		ar << _value.x;
		ar << _value.y;
		ar << _value.z;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator >> ( Axe::ArchiveDispatcher & ar, Position & _value )
	{
		ar >> _value.x;
		ar >> _value.y;
		ar >> _value.z;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & ar, const Pivot & _value )
	{
		ar << _value.pos;
		ar << _value.dir;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator >> ( Axe::ArchiveDispatcher & ar, Pivot & _value )
	{
		ar >> _value.pos;
		ar >> _value.dir;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( Axe::ArchiveInvocation & ar, const MoveDesc & _value )
	{
		ar << _value.pos;
		ar << _value.dir;
		ar << _value.timeStamp;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator >> ( Axe::ArchiveDispatcher & ar, MoveDesc & _value )
	{
		ar >> _value.pos;
		ar >> _value.dir;
		ar >> _value.timeStamp;
	}
}
