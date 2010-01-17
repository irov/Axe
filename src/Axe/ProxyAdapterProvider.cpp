#	include "pch.hpp"

#	include <Axe/ProxyAdapterProvider.hpp>
#	include <Axe/Connection.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	ProxyAdapterProvider::ProxyAdapterProvider( const ConnectionPtr & _connection )
		: m_connection(_connection)
	{

	}
	//////////////////////////////////////////////////////////////////////////
	const ConnectionPtr & ProxyAdapterProvider::getConnection() const
	{
		return m_connection;
	}
	//////////////////////////////////////////////////////////////////////////
	void ProxyAdapterProvider::setConnection( const ConnectionPtr & _connection )
	{
		m_connection = _connection;
	}
}