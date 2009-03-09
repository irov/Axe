#	include "pch.hpp"
#	include "Host.hpp"

#	include "AdapterSession.hpp"
#	include "AdapterConnection.hpp"

#	include "Servant.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Host::Host( boost::asio::io_service & _service, const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name )
		: Service(_service, _endpoint, _name)
		, m_hostId(0)
	{
		m_connectionCache = new ConnectionCache( this );
	}
	//////////////////////////////////////////////////////////////////////////
	bool Host::addServantByID( const ServantPtr & _servant, std::size_t _servantId )
	{
		_servant->setHost( this );

		bool inserted = m_servants.insert( std::make_pair( _servantId, _servant ) ).second;

		return inserted;
	}
	//////////////////////////////////////////////////////////////////////////
	void Host::setHostId( std::size_t _hostId )
	{
		m_hostId = _hostId;
	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t Host::getHostId() const
	{
		return m_hostId;
	}
	//////////////////////////////////////////////////////////////////////////
	void Host::dispatchMethod( std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, const SessionPtr & _session )
	{
		TMapServants::iterator it_find = m_servants.find( _servantId );

		if( it_find == m_servants.end() )
		{
			return;
		}

		const ServantPtr & servant = it_find->second;

		try
		{
			servant->callMethod( _methodId, _requestId, _session );
		}
		catch( const Exception & _ex )
		{
			servant->responseException( _methodId, _requestId, _session, _ex );
		}
		catch( const std::exception & _ex )
		{
			ArchiveWrite & aw = _session->beginException( _requestId );
			const char * message = _ex.what();
			aw << LocalException( message );
			_session->process();
		}
		catch( ... )
		{
			ArchiveWrite & aw = _session->beginException( _requestId );
			aw << UnknownException();
			_session->process();
		}
	}
}