#	include "pch.hpp"

#	include <Axe/Host.hpp>

#	include <Axe/AdapterSession.hpp>
#	include <Axe/AdapterConnection.hpp>

#	include <Axe/ServantProvider.hpp>

#	include <Axe/Proxy.hpp>
#	include <Axe/Servant.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Host::Host( boost::asio::io_service & _service, const ConnectionCachePtr & _connectionCache, const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name, std::size_t _hostId )
		: Service(_service, _endpoint, _name)
		, m_connectionCache(_connectionCache)
		, m_hostId(_hostId)
	{		
	}
	//////////////////////////////////////////////////////////////////////////
	ProxyPtr Host::addServant( std::size_t _servantId, const ServantPtr & _servant )
	{
		bool inserted = m_servants.insert( std::make_pair( _servantId, _servant ) ).second;

		if( inserted == false )
		{
			printf("Host::addServant host '%d' already exist servant '%d'\n"
				, m_hostId
				, _servantId 
				);

			return 0;
		}

		_servant->setServantId( _servantId );
		_servant->setHostId( m_hostId );

		const ConnectionPtr & cn = m_connectionCache->getConnection( m_hostId );

		ProxyPtr proxy = new Proxy( _servantId, cn );

		return proxy;
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
	namespace
	{
		class HostServantProviderResponse
			: public ServantProviderResponse
		{
		public:
			HostServantProviderResponse( const HostPtr & _host, std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const SessionPtr & _session )
				: m_host(_host)
				, m_servantId(_servantId)
				, m_methodId(_methodId)
				, m_requestId(_requestId)
				, m_archive(_archive)
				, m_session(_session)
			{
			}

		protected:
			void onServant( const ServantPtr & _servant ) override
			{
				m_host->addServant( m_servantId, _servant );
				m_host->dispatchMethod( m_servantId, m_methodId, m_requestId, m_archive, m_session );
			}

		protected:
			HostPtr m_host;
			std::size_t m_servantId;
			std::size_t m_methodId;
			std::size_t m_requestId;
			ArchiveDispatcher m_archive;
			SessionPtr m_session;
		};

		typedef AxeHandle<HostServantProviderResponse> HostServantProviderResponsePtr;
	}
	//////////////////////////////////////////////////////////////////////////
	void Host::dispatchMethod( std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const SessionPtr & _session )
	{
		TMapServants::iterator it_find = m_servants.find( _servantId );

		if( it_find == m_servants.end() )
		{
			HostServantProviderResponsePtr response =
				new HostServantProviderResponse( this, _servantId, _methodId, _requestId, _archive, _session );

			m_servantProvider->get( _servantId, response );

			return;
		}

		const ServantPtr & servant = it_find->second;

		try
		{
			servant->callMethod( _methodId, _requestId, _archive, _session );
		}
		catch( const Exception & _ex )
		{
			servant->responseException( _methodId, _requestId, _session, _ex );
		}
		catch( const std::exception & _ex )
		{
			ArchiveInvocation & aw = _session->beginException( _requestId );
			const char * message = _ex.what();
			aw << LocalException( message );
			_session->process();
		}
		catch( ... )
		{
			ArchiveInvocation & aw = _session->beginException( _requestId );
			aw << UnknownException();
			_session->process();
		}
	}
	//////////////////////////////////////////////////////////////////////////
	const ConnectionCachePtr & Host::getConnectionCahce() const
	{
		return m_connectionCache;
	}
}