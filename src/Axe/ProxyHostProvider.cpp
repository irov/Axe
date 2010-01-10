#	include "pch.hpp"

#	include <Axe/ProxyHostProvider.hpp>
#	include <Axe/Connection.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	ProxyHostProvider::ProxyHostProvider( const ConnectionPtr & _connection )
		: m_connection(_connection)
	{

	}
	//////////////////////////////////////////////////////////////////////////
	const ConnectionPtr & ProxyHostProvider::getConnection() const
	{
		return m_connection;
	}
	//////////////////////////////////////////////////////////////////////////
	void ProxyHostProvider::setConnection( const ConnectionPtr & _connection )
	{
		m_connection = _connection;
	}
}