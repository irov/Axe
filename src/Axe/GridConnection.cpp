#	include "pch.hpp"

#	include "GridConnection.hpp"

#	include "Session.hpp"
#	include "Adapter.hpp"
#	include "Response.hpp"

#	include "ArchiveWrite.hpp"
#	include "ArchiveRead.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	GridConnection::GridConnection( boost::asio::io_service & _service, const AdapterConnectResponsePtr & _connectResponse )
		: Invocation( _service, 0 )
		, m_connectResponse(_connectResponse)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void GridConnection::registerAdapter( const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name )
	{
		ArchiveWrite & ar = this->connect( _endpoint );

		ar.writeString( _name );

		this->processMessage();
	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveWrite & GridConnection::beginMessage( std::size_t _servantId, std::size_t _methodId, const ResponsePtr & _response )
	{
		//Fake
		ArchiveWrite & ar = this->getArchiveWrite();

		return ar;
	}
	//////////////////////////////////////////////////////////////////////////
	void GridConnection::dispatchMessage( ArchiveRead & _ar, std::size_t _size )
	{
		//Empty
	}
	//////////////////////////////////////////////////////////////////////////
	void GridConnection::connectionSuccessful( ArchiveRead & _ar, std::size_t _size )
	{
		std::size_t id;

		_ar.read( id );

		m_connectResponse->connectSuccessful( id );
	}
	//////////////////////////////////////////////////////////////////////////
	void GridConnection::connectionFailed( ArchiveRead & _ar, std::size_t _size )
	{
		m_connectResponse->connectFailed();
	}
}