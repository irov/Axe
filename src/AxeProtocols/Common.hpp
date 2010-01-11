#	pragma once

#	include <Axe/Bellhop.hpp>
#	include <Axe/Servant.hpp>
#	include <Axe/Response.hpp>
#	include <Axe/Proxy.hpp>
#	include <Axe/Response.hpp>
#	include <Axe/Exception.hpp>

namespace Axe
{
	class ArchiveInvocation;
	class ArchiveDispatcher;
}

namespace AxeProtocol
{
	
	struct Direction
	{
		float x;
		float y;
		float z;
	};
	
	void operator << ( Axe::ArchiveInvocation & ar, const Direction & _value );
	void operator >> ( Axe::ArchiveDispatcher & ar, Direction & _value );
	
	struct Position
	{
		float x;
		float y;
		float z;
	};
	
	void operator << ( Axe::ArchiveInvocation & ar, const Position & _value );
	void operator >> ( Axe::ArchiveDispatcher & ar, Position & _value );
	
	struct Pivot
	{
		Position pos;
		Direction dir;
	};
	
	void operator << ( Axe::ArchiveInvocation & ar, const Pivot & _value );
	void operator >> ( Axe::ArchiveDispatcher & ar, Pivot & _value );
	
	struct MoveDesc
	{
		Position pos;
		Direction dir;
		double timeStamp;
	};
	
	void operator << ( Axe::ArchiveInvocation & ar, const MoveDesc & _value );
	void operator >> ( Axe::ArchiveDispatcher & ar, MoveDesc & _value );
}
