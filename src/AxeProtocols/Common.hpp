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
	
	
	struct Position
	{
		float x;
		float y;
		float z;
	};
	
	
	struct Pivot
	{
		Position pos;
		Direction dir;
	};
	
	
	struct MoveDesc
	{
		Position pos;
		Direction dir;
		double timeStamp;
	};
	
}
namespace Axe
{
	void operator << ( Axe::ArchiveInvocation & ar, const ::AxeProtocol::Direction & _value );
	void operator >> ( Axe::ArchiveDispatcher & ar, ::AxeProtocol::Direction & _value );
	void operator << ( Axe::ArchiveInvocation & ar, const ::AxeProtocol::Position & _value );
	void operator >> ( Axe::ArchiveDispatcher & ar, ::AxeProtocol::Position & _value );
	void operator << ( Axe::ArchiveInvocation & ar, const ::AxeProtocol::Pivot & _value );
	void operator >> ( Axe::ArchiveDispatcher & ar, ::AxeProtocol::Pivot & _value );
	void operator << ( Axe::ArchiveInvocation & ar, const ::AxeProtocol::MoveDesc & _value );
	void operator >> ( Axe::ArchiveDispatcher & ar, ::AxeProtocol::MoveDesc & _value );
}
