#	pragma once

#	include <AxeUtil/Shared.hpp>

namespace Axe
{
	typedef AxeHandle<class Connection> ConnectionPtr; 

	class ProxyConnectionProvider
		: virtual public AxeUtil::Shared
	{
	public:
		ProxyConnectionProvider( const ConnectionPtr & _connection );

	public:
		const ConnectionPtr & getConnection() const;
		void setConnection( const ConnectionPtr & _connection );

	protected:
		ConnectionPtr m_connection;
	};

	typedef AxeHandle<ProxyConnectionProvider> ProxyConnectionProviderPtr;

}