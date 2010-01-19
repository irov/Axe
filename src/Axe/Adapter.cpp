#	include "pch.hpp"

#	include <Axe/Adapter.hpp>

#	include <Axe/Communicator.hpp>

#	include <Axe/AdapterException.hpp>
#	include <Axe/AdapterSession.hpp>
#	include <Axe/AdapterConnection.hpp>

#	include <Axe/ServantFactory.hpp>
#	include <Axe/ServantProvider.hpp>

#	include <Axe/Proxy.hpp>
#	include <Axe/Servant.hpp>
#	include <Axe/Response.hpp>
#	include <Axe/RouterResponse.hpp>

#	include <Axe/DispatcherException.hpp>

#	include <AxeProtocols/EvictorManager.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	namespace
	{
		class AdapterServantProviderResponse
			: public ServantProviderResponse
		{
		public:
			AdapterServantProviderResponse( const AdapterPtr & _adapter, std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const SessionPtr & _session )
				: m_adapter(_adapter)
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
				m_adapter->addServantWithId( m_servantId, _servant );

				_servant->dispatchMethod( m_methodId, m_requestId, m_archive, m_session );
			}

			void onServantReplace( std::size_t _adapterId )
			{
				m_adapter->replaceMethod( m_servantId, m_methodId, m_requestId, m_archive, m_session, _adapterId );
			}

			void onServantNotFound( std::size_t _servantId )
			{
				m_adapter->exceptionMethod( _servantId, m_requestId, m_session );
			}

		protected:
			AdapterPtr m_adapter;
			std::size_t m_servantId;
			std::size_t m_methodId;
			std::size_t m_requestId;
			ArchiveDispatcher m_archive;
			SessionPtr m_session;
		};

		typedef AxeHandle<AdapterServantProviderResponse> AdapterServantProviderResponsePtr;
	}
	//////////////////////////////////////////////////////////////////////////
	Adapter::Adapter( const CommunicatorPtr & _communicator, const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name, std::size_t _adapterId )
		: Service(_communicator->getService(), _endpoint, _name)
		, m_communicator(_communicator)
		, m_adapterId(_adapterId)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	const CommunicatorPtr & Adapter::getCommunicator() const
	{
		return m_communicator;
	}
	//////////////////////////////////////////////////////////////////////////
	bool Adapter::addServantWithId( std::size_t _servantId, const ServantPtr & _servant )
	{
		bool inserted = m_servants.insert( std::make_pair( _servantId, _servant ) ).second;

		if( inserted == false )
		{
			return false;
		}

		_servant->setAdapterId( m_adapterId );
		_servant->setServantId( _servantId );	

		return true;
	}
	//////////////////////////////////////////////////////////////////////////
	namespace
	{
		class AdapterServantFactoryCreateResponse
			: public ServantFactoryCreateResponse
		{
		public:
			AdapterServantFactoryCreateResponse( const AdapterPtr & _adapter, const AdapterCreateServantResponsePtr & _response )
				: m_adapter(_adapter)
				, m_response(_response)
			{
			}

		public:
			void onServantCreate( const ServantPtr & _servant ) override
			{
				const CommunicatorPtr & communicator = m_adapter->getCommunicator();

				const Proxy_EvictorManagerPtr & evictorManager = communicator->getEvictorManager();

				std::size_t adapterId = m_adapter->getAdapterId();

				evictorManager->create_async( 
					bindResponse( boost::bind( &AdapterServantFactoryCreateResponse::addServantResponse, handlePtr(this), _1, _servant ) )
					, adapterId 
					);
			}

			void addServantResponse( std::size_t _servantId, const ServantPtr & _servant )
			{
				if( m_adapter->addServantWithId( _servantId, _servant ) == false )
				{
					std::size_t adapterId = m_adapter->getAdapterId();

					printf("Adapter::addServant adapter '%d' already exist servant '%d'\n"
						, adapterId
						, _servantId 
						);

					AdapterServantAlreadyExistException ex;
					ex.adapterId = adapterId;
					ex.servantId = _servantId;

					m_response->onServantCreateFailed( _servant, ex );
				}
				else
				{
					m_response->onServantCreateSuccessful( _servant );
				}
			}

		protected:
			AdapterPtr m_adapter;
			AdapterCreateServantResponsePtr m_response;
		};
	}
	//////////////////////////////////////////////////////////////////////////
	void Adapter::addServant( const std::string & _type, const AdapterCreateServantResponsePtr & _response )
	{
		const ServantFactoryPtr & servantFactory = m_communicator->getServantFactory();

		servantFactory->genServant( _type
			, new AdapterServantFactoryCreateResponse( this, _response ) 
			);
	}
	//////////////////////////////////////////////////////////////////////////
	bool Adapter::hasServant( std::size_t _servantId ) const
	{
		TMapServants::const_iterator it_found = m_servants.find( _servantId );

		return it_found != m_servants.end();
	}
	//////////////////////////////////////////////////////////////////////////
	static void removeServantResponse( const ProxyPtr & _proxy, const AdapterRemoveServantResponsePtr & _response )
	{
		_proxy->destroy_async(
			bindResponse( boost::bind( &AdapterRemoveServantResponse::onServantRemoveSuccessful, _response ), boost::bind( &AdapterRemoveServantResponse::onServantRemoveFailed, _response, _1 ) )
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Adapter::removeServant( const ProxyPtr & _proxy, const AdapterRemoveServantResponsePtr & _response )
	{
		std::size_t servantId = _proxy->getServantId();

		const Proxy_EvictorManagerPtr & evictor = m_communicator->getEvictorManager();

		evictor->erase_async(
			bindResponse( boost::bind( &removeServantResponse, _proxy, _response ) )
			, servantId
			);
		//_proxy->destroy_async(  )
	}
	//////////////////////////////////////////////////////////////////////////
	void Adapter::setAdapterId( std::size_t _adapterId )
	{
		m_adapterId = _adapterId;
	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t Adapter::getAdapterId() const
	{
		return m_adapterId;
	}
	//////////////////////////////////////////////////////////////////////////
	SessionPtr Adapter::makeSession()
	{
		const ConnectionCachePtr & connectionCache = m_communicator->getConnectionCache();

		AdapterSessionPtr session = new AdapterSession( m_acceptor.get_io_service(), this, connectionCache );

		return session;
	}
	//////////////////////////////////////////////////////////////////////////
	void Adapter::dispatchMethod( std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const SessionPtr & _session )
	{
		TMapServants::iterator it_find = m_servants.find( _servantId );

		if( it_find == m_servants.end() )
		{
			AdapterServantProviderResponsePtr response =
				new AdapterServantProviderResponse( this, _servantId, _methodId, _requestId, _archive, _session );

			const ServantProviderPtr & servantProvider = m_communicator->getServantProvider();

			servantProvider->get( _servantId, m_adapterId, response );
			return;
		}

		const ServantPtr & servant = it_find->second;

		servant->dispatchMethod( _methodId, _requestId, _archive, _session );
	}
	//////////////////////////////////////////////////////////////////////////
	void Adapter::replaceMethod( std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const SessionPtr & _session, std::size_t _adapterId )
	{
		{
			const ConnectionCachePtr & connectionCache = m_communicator->getConnectionCache();

			const ConnectionPtr & connection = connectionCache->getConnection( _adapterId );

			ArchiveInvocation & ar = connection->beginMessage( _servantId, _methodId, new RouterResponse( _requestId, _session ) );

			ar << _archive;

			connection->processMessage();
		}

		{
			ArchiveInvocation & ar = _session->beginException( _requestId );

			DispatcherServantRelocateException ex;
			ex.servantId = _servantId;
			ex.adapterId = _adapterId;

			ar.writeSize( DispatcherServantRelocateException::exceptionId );
			ex.write( ar );

			_session->process();
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void Adapter::exceptionMethod( std::size_t _servantId, std::size_t _requestId, const SessionPtr & _session )
	{
		ArchiveInvocation & ar = _session->beginException( _requestId );

		DispatcherObjectNotFoundException ex;
		ex.servantId = _servantId;
		ex.adapterId = m_adapterId;

		ar.writeSize( DispatcherObjectNotFoundException::exceptionId );
		ex.write( ar );

		_session->process();
	}
}