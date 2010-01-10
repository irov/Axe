#	include "pch.hpp"

#	include <Axe/Host.hpp>

#	include <Axe/Communicator.hpp>
#	include <Axe/Exception.hpp>

#	include <Axe/AdapterSession.hpp>
#	include <Axe/AdapterConnection.hpp>

#	include <Axe/ServantProvider.hpp>

#	include <Axe/Proxy.hpp>
#	include <Axe/Servant.hpp>
#	include <Axe/Response.hpp>

#	include <Axe/DispatcherException.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Host::Host( const CommunicatorPtr & _communicator, const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name, std::size_t _hostId )
		: Service(_communicator->getService(), _endpoint, _name)
		, m_communicator(_communicator)
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

		const ConnectionCachePtr & connectionCache = m_communicator->getConnectionCache();

		ProxyPtr proxy = _servant->getProxy( connectionCache );

		return proxy;
	}
	//////////////////////////////////////////////////////////////////////////
	bool Host::hasServant( std::size_t _servantId ) const
	{
		TMapServants::const_iterator it_found = m_servants.find( _servantId );

		return it_found != m_servants.end();
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
				if( m_host->hasServant(m_servantId) )
				{
					m_host->addServant( m_servantId, _servant );
				}
				
				m_host->dispatchMethod( m_servantId, m_methodId, m_requestId, m_archive, m_session );
			}

			void onServantReplace( std::size_t _hostId )
			{
				m_host->replaceMethod( m_servantId, m_methodId, m_requestId, m_archive, m_session, _hostId );
			}

			void onServantNotFound( std::size_t _servantId )
			{
				m_host->exceptionMethod( _servantId, m_requestId, m_session );
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

			const ServantProviderPtr & servantProvider = m_communicator->getServantProvider();

			servantProvider->get( _servantId, m_hostId, response );
			return;
		}

		const ServantPtr & servant = it_find->second;

		try
		{
			servant->callMethod( _methodId, _requestId, _archive, _session );
		}
		catch( const ProtocolException & _ex )
		{
			servant->responseException( _methodId, _requestId, _session, _ex );
		}
		catch( ... )
		{
			ArchiveInvocation & aw = _session->beginException( _requestId );

			writeExceptionFilter( aw );

			_session->process();
		}
	}
	//////////////////////////////////////////////////////////////////////////
	namespace
	{
		class ResponseReplaceMethod
			: public Response
		{
		public:
			ResponseReplaceMethod( std::size_t _requestId, const SessionPtr & _session )
				: m_requestId(_requestId)
				, m_session(_session)
			{
			}

		protected:
			void responseCall( ArchiveDispatcher & _ar, std::size_t _size ) override
			{
				ArchiveInvocation & aw = m_session->beginResponse( m_requestId );

				AxeUtil::Archive::iterator it_select = aw.selectArchive( _size );
				_ar.readArchive( it_select, _size );

				m_session->process();
			}

			void exceptionCall( ArchiveDispatcher & _ar, std::size_t _size ) override
			{
				ArchiveInvocation & aw = m_session->beginException( m_requestId );

				AxeUtil::Archive::iterator it_select = aw.selectArchive( _size );
				_ar.readArchive( it_select, _size );

				m_session->process();
			}

		protected:
			void throw_exception( const Exception & _ex ) override
			{
				//Empty
			}

		protected:
			std::size_t m_requestId;
			SessionPtr m_session;
		};
	}
	//////////////////////////////////////////////////////////////////////////
	void Host::replaceMethod( std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const SessionPtr & _session, std::size_t _hostId )
	{
		{
			const ConnectionCachePtr & connectionCache = m_communicator->getConnectionCache();

			const ConnectionPtr & connection = connectionCache->getConnection( _hostId );

			ArchiveInvocation & ar = connection->beginMessage( _servantId, _methodId, new ResponseReplaceMethod( _requestId, _session ) );

			ar << _archive;

			connection->processMessage();
		}

		{
			ArchiveInvocation & ar = _session->beginException( _requestId );
		
			DispatcherServantRelocateException ex;
			ex.servantId = _servantId;
			ex.hostId = _hostId;
			
			ar.writeSize( ex.getId() );
			ex.write( ar );

			_session->process();
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void Host::exceptionMethod( std::size_t _servantId, std::size_t _requestId, const SessionPtr & _session )
	{
		ArchiveInvocation & ar = _session->beginException( _requestId );

		DispatcherObjectNotFoundException ex;
		ex.servantId = _servantId;
		ex.hostId = m_hostId;

		ar.writeSize( ex.getId() );
		ex.write( ar );

		_session->process();
	}
}