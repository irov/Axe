#	include "pch.hpp"

#	include "ConnectionException.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	ConnectionSocketException::ConnectionSocketException( const boost::system::error_code & _code )
		: code(_code)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void ConnectionSocketException::rethrow() const
	{
		throw ConnectionSocketException(code);
	}
	//////////////////////////////////////////////////////////////////////////
	void ConnectionSocketException::write( ArchiveInvocation & _ar ) const
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void ConnectionSocketException::read( ArchiveDispatcher & _ar )
	{
	}
}