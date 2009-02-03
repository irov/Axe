#	pragma once

#	include "Session.hpp"
#	include "Adapter.hpp"

namespace Axe
{
	class ArchiveWrite;

	class AdapterSession
		: public Session
	{
	public:
		AdapterSession( boost::asio::io_service & _service, const AdapterPtr & _adapter );

	public:
		ArchiveWrite & beginResponse( std::size_t _responseId );

	public:
		void dispatchMessage( ArchiveRead & _ar, std::size_t _size ) override;
		void permissionVerify( ArchiveRead & _ar, std::size_t _size ) override;

	protected:
		AdapterPtr m_adapter;
	};

	typedef AxeHandle<AdapterSession> AdapterSessionPtr;
}