#	pragma once

#	include "HostSession.hpp"

namespace Axe
{
	class ArchiveWrite;

	class AdapterSession
		: public HostSession
	{
	public:
		AdapterSession( boost::asio::io_service & _service, const HostPtr & _host, const ConnectionCachePtr & _connectionCache );

	public:
		void permissionVerify( ArchiveRead & _ar, std::size_t _size ) override;
	};

	typedef AxeHandle<AdapterSession> AdapterSessionPtr;
}