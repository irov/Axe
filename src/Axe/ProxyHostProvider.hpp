#	pragma once

#	include <AxeUtil/Shared.hpp>

namespace Axe
{
	typedef AxeHandle<class Connection> ConnectionPtr; 

	class ProxyHostProvider
		: virtual public AxeUtil::Shared
	{
	public:
		ProxyHostProvider( const ConnectionPtr & _connection );

	public:
		const ConnectionPtr & getConnection() const;
		void setConnection( const ConnectionPtr & _connection );

	protected:
		ConnectionPtr m_connection;
	};

	typedef AxeHandle<ProxyHostProvider> ProxyHostProviderPtr;

}