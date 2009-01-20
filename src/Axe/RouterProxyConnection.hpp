#	pragma once

#	include "Connection.hpp"

namespace Axe
{
	typedef AxeHandle<class RouterConnection> RouterConnectionPtr;

	class ArchiveWrite;

	class RouterProxyConnection
		: public Connection
	{
	public:
		RouterProxyConnection( const RouterConnectionPtr & _base, std::size_t _id );

	public:
		ArchiveWrite & beginMessage( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response ) override;

		void procces() override;

	protected:
		RouterConnectionPtr m_base;
		std::size_t m_id;
	};

	typedef AxeHandle<RouterProxyConnection> RouterProxyConnectionPtr;
}