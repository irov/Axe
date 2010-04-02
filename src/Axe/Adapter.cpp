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
	Adapter::Adapter( const CommunicatorPtr & _communicator, const boost::asio::ip::tcp::endpoint & _endpoint, std::size_t _adapterId )
		: Acceptor(_communicator->getService(), _endpoint)
		, m_communicator(_communicator)
		, m_adapterId(_adapterId)
	{
		m_servantProvider = new ServantProvider( m_communicator, _adapterId );
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
	void Adapter::addServantResponse_( std::size_t _servantId, const ServantPtr & _servant, const AdapterCreateServantResponsePtr & _response )
	{
		if( this->addServantWithId( _servantId, _servant ) == false )
		{
			printf("Adapter::addServant adapter '%d' already exist servant '%d'\n"
				, m_adapterId
				, _servantId 
				);

			AdapterServantAlreadyExistException ex;
			ex.adapterId = m_adapterId;
			ex.servantId = _servantId;

			const Proxy_EvictorManagerPtr & evictorManager = m_communicator->getEvictorManager();

			evictorManager->erase_async( 
				bindResponse( boost::bind( &AdapterCreateServantResponse::onServantCreateFailed, _response, ex )
					, boost::bind( &AdapterCreateServantResponse::onServantCreateFailed, _response, _1 ) 
					)
				, _servantId
				);
		}
		else
		{
			_response->onServantCreateSuccessful( _servant );
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void Adapter::addServant( const std::string & _type, const AdapterCreateServantResponsePtr & _response )
	{
		const ServantFactoryPtr & servantFactory = m_communicator->getServantFactory();

		ServantPtr servant = servantFactory->genServant( _type );

		if( servant == 0 )
		{
			AdapterServantFactoryNotRegistredGeneratorException ex;
			ex.servantType = _type;
			ex.adapterId = m_adapterId;

			_response->onServantCreateFailed( ex );
			return;
		}

		const Proxy_EvictorManagerPtr & evictorManager = m_communicator->getEvictorManager();

		evictorManager->create_async( 
			bindResponse( boost::bind( &Adapter::addServantResponse_, handlePtr(this), _1, servant, _response )
				, boost::bind( &AdapterCreateServantResponse::onServantCreateFailed, _response, _1 ) 
				)
			, m_adapterId
			, _type
			);
	}
	//////////////////////////////////////////////////////////////////////////
	void Adapter::addUnique( const std::string & _name, const std::string & _type, const AdapterCreateServantResponsePtr & _response )
	{
		const ServantFactoryPtr & servantFactory = m_communicator->getServantFactory();

		ServantPtr servant = servantFactory->genServant( _type );

		if( servant == 0 )
		{
			AdapterServantFactoryNotRegistredGeneratorException ex;
			ex.servantType = _type;
			ex.adapterId = m_adapterId;

			if( _response )
			{
				_response->onServantCreateFailed( ex );
			}
		}
		else
		{
			TMapUniques::iterator it_insert = m_uniques.insert( std::make_pair(_name, servant) ).first;

			if( _response )
			{
				_response->onServantCreateSuccessful( it_insert->second );
			}
		}
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

		SocketPtr socket = m_communicator->createSocket();

		AdapterSessionPtr session = new AdapterSession( socket, connectionCache, this );

		return session;
	}
	//////////////////////////////////////////////////////////////////////////
	void Adapter::dispatchMethod( std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const SessionPtr & _session )
	{
		if( _servantId == 0 )
		{
			std::string uniqueId;
			_archive.readString( uniqueId );

			TMapUniques::iterator it_found = m_uniques.find( uniqueId );

			if( it_found == m_uniques.end() )
			{
				DispatcherServantNotFoundException ex;
				ex.servantId = _servantId;
				ex.adapterId = m_adapterId;

				_session->processException( _requestId, DispatcherServantNotFoundException::exceptionId, ex );
				return;
			}

			const ServantPtr & servant = it_found->second;

			servant->dispatchMethod( _methodId, _requestId, _archive, _session );
			return;
		}

		TMapServants::iterator it_found = m_servants.find( _servantId );

		if( it_found == m_servants.end() )
		{
			AdapterServantProviderResponsePtr response =
				new AdapterServantProviderResponse( this, _servantId, _methodId, _requestId, _archive, _session );

			m_servantProvider->get( _servantId, response );
		}
		else
		{
			const ServantPtr & servant = it_found->second;

			servant->dispatchMethod( _methodId, _requestId, _archive, _session );
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void Adapter::replaceMethod( std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const SessionPtr & _session, std::size_t _adapterId )
	{
		{
			const ConnectionCachePtr & connectionCache = m_communicator->getConnectionCache();

			const ConnectionPtr & connection = connectionCache->getAdapterConnection( _adapterId );

			ArchiveInvocation & ar = connection->beginMessage( _servantId, _methodId, new RouterResponse( _requestId, _session ) );

			ar << _archive;

			connection->process();
		}

		{
			DispatcherServantRelocateException ex;
			ex.servantId = _servantId;
			ex.adapterId = _adapterId;

			_session->processException( _requestId, DispatcherServantRelocateException::exceptionId, ex );
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void Adapter::exceptionMethod( std::size_t _servantId, std::size_t _requestId, const SessionPtr & _session )
	{
		DispatcherServantNotFoundException ex;
		ex.servantId = _servantId;
		ex.adapterId = m_adapterId;

		_session->processException( _requestId, DispatcherServantNotFoundException::exceptionId, ex );
	}
}