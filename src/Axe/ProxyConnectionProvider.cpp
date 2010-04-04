#	include "pch.hpp"

#	include <Axe/ProxyConnectionProvider.hpp>
#	include <Axe/Connection.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	ProxyConnectionProvider::ProxyConnectionProvider( const ConnectionPtr & _connection )
		: m_connection(_connection)
	{

	}
	//////////////////////////////////////////////////////////////////////////
	const ConnectionPtr & ProxyConnectionProvider::getConnection() const
	{
		return m_connection;
	}
	//////////////////////////////////////////////////////////////////////////
	void ProxyConnectionProvider::setConnection( const ConnectionPtr & _connection )
	{
		m_connection = _connection;
	}
}