#	pragma once

#	include "Session.hpp"

namespace Axe
{
	typedef AxeHandle<class Adapter> AdapterPtr;

	class AdapterSession
		: public Session
	{
	public:
		AdapterSession( boost::asio::io_service & _service, const AdapterPtr & _adapter );

	public:
		ArchiveWrite & beginResponse( std::size_t _responseId );

	public:
		void dispatchMessage( std::size_t _size ) override;

	protected:
		AdapterPtr m_adapter;
	};
}