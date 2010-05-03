#	pragma once

#	include <AxeUtil/Shared.hpp>
#	include <AxeUtil/Archive.hpp>

namespace Axe
{
	class ArchiveInvocation;
	class ArchiveDispatcher;

	typedef AxeHandle<class Response> ResponsePtr;

	class Dispatcher
		: virtual public AxeUtil::Shared
	{
	public:
		Dispatcher();
		
	public:
		void invokeMethod( ArchiveInvocation & _archive, std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response );
		void dispatchResponse( ArchiveDispatcher & _ar, std::size_t _size );

	protected:
		std::size_t addDispatch_( const ResponsePtr & _response );

	protected:
		std::size_t m_messageEnum;

		typedef std::map<std::size_t, ResponsePtr> TMapResponse;
		TMapResponse m_dispatch;
	};
}