#	pragma once

#	include <Axe/Session.hpp>

namespace Axe
{
	typedef AxeHandle<class Adapter> AdapterPtr;

	class AdapterSession
		: public Session
	{
	public:
		AdapterSession( boost::asio::io_service & _service, const AdapterPtr & _adapter, const ConnectionCachePtr & _connectionCache );

	public:
		void dispatchMessage( ArchiveDispatcher & _ar, std::size_t _size ) override;
		void permissionVerify( ArchiveDispatcher & _ar, std::size_t _size ) override;

	protected:
		AdapterPtr m_adapter;
	};

	typedef AxeHandle<AdapterSession> AdapterSessionPtr;
}