#	include "pch.hpp"

#	include "Dispatcher.hpp"
#	include "Exception.hpp"

#	include "Response.hpp"

#	include <Axe/ArchiveInvocation.hpp>
#	include <Axe/ArchiveDispatcher.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Dispatcher::Dispatcher()
		: m_messageEnum(0)
	{

	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t Dispatcher::addDispatch_( const ResponsePtr & _response )
	{
		if( _response == 0 )
		{
			return 0;
		}

		++m_messageEnum;
		m_dispatch.insert( std::make_pair( m_messageEnum, _response ) );

		return m_messageEnum;
	}
	//////////////////////////////////////////////////////////////////////////
	void Dispatcher::invokeMethod( ArchiveInvocation & _archive, std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response )
	{
		std::size_t messageId = this->addDispatch_( _response );

		_archive << _servantId;

		_archive.writeSize( _methodId );
		_archive.writeSize( messageId );
	}
	//////////////////////////////////////////////////////////////////////////
	void Dispatcher::dispatchResponse( ArchiveDispatcher & _ar, std::size_t _size )
	{
		std::size_t responseId;
		_ar.readSize( responseId );

		TMapResponse::iterator it_found = m_dispatch.find( responseId );

		if( it_found == m_dispatch.end() )
		{
			throw ProtocolMismatchException();
		}

		const ResponsePtr & response = it_found->second;

		if( response->dispatch( _ar, _size ) == true )
		{
			m_dispatch.erase( it_found );
		}

		if( m_dispatch.empty() )
		{
			m_messageEnum = 0;
		}
	}

}