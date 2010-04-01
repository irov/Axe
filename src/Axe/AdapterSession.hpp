#	pragma once

#	include <Axe/Session.hpp>

namespace Axe
{
	typedef AxeHandle<class Adapter> AdapterPtr;

	class AdapterSession
		: public Session
	{
	public:
		AdapterSession( const SocketPtr & _socket, const ConnectionCachePtr & _connectionCache, const AdapterPtr & _adapter );

	public:
		void dispatchMessage( ArchiveDispatcher & _ar, std::size_t _size ) override;
		void permissionVerify( ArchiveDispatcher & _ar, std::size_t _size ) override;

	protected:
		AdapterPtr m_adapter;
	};

	typedef AxeHandle<AdapterSession> AdapterSessionPtr;
}