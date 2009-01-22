#	include "pch.hpp"

#	include "AdapterConnection.hpp"

#	include "Session.hpp"
#	include "Adapter.hpp"
#	include "Response.hpp"

#	include "ArchiveWrite.hpp"
#	include "ArchiveRead.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	class AdapterSessionConnection
		: public Session
	{
	public:
		AdapterSessionConnection( boost::asio::io_service & _service, AdapterConnection * _base )
			: Session( _service )
			, m_base(_base)
		{
		}
		
	public:
		void dispatchMessage( std::size_t _size ) override
		{
			ArchiveRead & _read = this->getArchiveRead();
			m_base->dispatchMessage( _read, _size );
		}

	protected:
		AdapterConnection * m_base;
	};
	
	//////////////////////////////////////////////////////////////////////////
	AdapterConnection::AdapterConnection( boost::asio::io_service & _service, std::size_t _endpointId )
		: Connection( _endpointId ) 
		, m_session( new AdapterSessionConnection( _service, this ) )
		, m_messageEnum(0)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void AdapterConnection::connect( const boost::asio::ip::tcp::endpoint & _endpoint )
	{
		m_session->connect( _endpoint );
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveWrite & AdapterConnection::beginMessage( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response )
	{
		ArchiveWrite & ar = m_session->getArchiveWrite();
		
		ar.begin();

		this->writeBody( ar, _servantId, _methodId, _response );

		return ar;
	}
	//////////////////////////////////////////////////////////////////////////
	void AdapterConnection::process()
	{
		m_session->process();
	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t AdapterConnection::addDispatch( const ResponsePtr & _response )
	{
		if( m_dispatch.empty() )
		{
			m_messageEnum = 0;
		}

		++m_messageEnum;
		m_dispatch.insert( std::make_pair( m_messageEnum, _response ) );

		return m_messageEnum;
	}
	//////////////////////////////////////////////////////////////////////////
	void AdapterConnection::writeBody( ArchiveWrite & _archive, std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response )
	{
		std::size_t messageId = this->addDispatch( _response );

		_archive.write( _servantId );
		_archive.writeSize( _methodId );
		_archive.writeSize( messageId );
	}
	//////////////////////////////////////////////////////////////////////////
	void AdapterConnection::dispatchMessage( ArchiveRead & _read, std::size_t _size )
	{
		std::size_t responseId;
		_read.readSize( responseId );

		TMapResponse::iterator it_found = m_dispatch.find( responseId );

		const ResponsePtr & response = it_found->second;
		response->responseCall( _read );

		m_dispatch.erase( it_found );

		_read.clear();
	}
	////////////////////////////////////////////////////////////////////////////
	//const ConnectionPtr & AdapterConnection::getConnection( std::size_t _id )
	//{
	//	TMapConnections::const_iterator it_found = m_connections.find( _id );
	//	
	//	if( it_found == m_connections.end() )
	//	{
	//		return 0;
	//	}
	//	return it_found->second;
	//}
}