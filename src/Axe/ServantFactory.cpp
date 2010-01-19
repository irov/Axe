#	include "pch.hpp"

#	include "ServantFactory.hpp"
#	include "ServantFactoryException.hpp"

#	include <AxeProtocols/GridManager.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	ServantFactory::ServantFactory( const Proxy_GridManagerPtr & _gridManager )
		: m_gridManager(_gridManager)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void ServantFactory::registerServantGenerator( std::size_t _typeId, const ServantFactoryGeneratorPtr & _generator )
	{
		m_generators.insert( std::make_pair(_typeId, _generator) );
	}
	//////////////////////////////////////////////////////////////////////////
	namespace
	{
		class ServantFactoryGenServantGetIdResponse
			: public ServantFactoryGetIdResponse
		{
		public:
			ServantFactoryGenServantGetIdResponse( const ServantFactoryPtr & _servantFactory, const ServantFactoryCreateResponsePtr & _cb )
				: m_servantFactory(_servantFactory)
				, m_cb(_cb)
			{
			}

		public:
			void onServantTypeIdSuccessful( std::size_t _id ) override
			{
				ServantPtr servant = m_servantFactory->genServantWithId( _id );

				if( servant )
				{
					m_cb->onServantCreateSuccessful( servant );
				}
				else
				{
					ServantFactoryGeneratorNotFoundException ex;
					ex.typeId = _id;

					this->onServantTypeIdFailed( ex );
				}
			}

			void onServantTypeIdFailed( const Axe::Exception & _ex ) override
			{
				m_cb->onServantCreateFailed( _ex );
			}

		protected:
			ServantFactoryPtr m_servantFactory;
			ServantFactoryCreateResponsePtr m_cb;
		};
	}
	//////////////////////////////////////////////////////////////////////////
	void ServantFactory::genServant( const std::string & _type, const ServantFactoryCreateResponsePtr & _response )
	{
		this->getTypeId( _type
			, new ServantFactoryGenServantGetIdResponse( this, _response ) 
			);
	}
	//////////////////////////////////////////////////////////////////////////
	ServantPtr ServantFactory::genServantWithId( std::size_t _typeId )
	{
		TMapServantGenerators::iterator it_found = m_generators.find( _typeId );

		if( it_found == m_generators.end() )
		{
			return 0;
		}

		return it_found->second->create();
	}
	//////////////////////////////////////////////////////////////////////////
	void ServantFactory::getTypeId( const std::string & _type, const ServantFactoryGetIdResponsePtr & _cb )
	{
		TMapIdCache::iterator it_found = m_ids.find( _type );

		if( it_found != m_ids.end() )
		{
			_cb->onServantTypeIdSuccessful( it_found->second );
		}
		else
		{
			this->provideTypeId( _type, _cb );
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void ServantFactory::provideTypeId( const std::string & _type, const ServantFactoryGetIdResponsePtr & _cb )
	{
		TMapWantedIdResponse::iterator it_found = m_wantedIds.find( _type );

		if( it_found == m_wantedIds.end() )
		{
			TListWantedIdResponse responses;
		
			m_gridManager->getServantTypeId_async( 
				bindResponse( boost::bind( &ServantFactory::getTypeIdResponse, handlePtr(this), _1, _type )
				, boost::bind( &ServantFactory::getTypeIdException, handlePtr(this), _1, _type ) )
				, _type 
				);

			it_found = m_wantedIds.insert( std::make_pair(_type, responses) ).first;
		}
		
		it_found->second.push_back( _cb );
	}
	//////////////////////////////////////////////////////////////////////////
	void ServantFactory::getTypeIdResponse( std::size_t _typeId, const std::string & _type )
	{
		m_ids.insert( std::make_pair( _type, _typeId ) );

		TMapWantedIdResponse::iterator it_found = m_wantedIds.find( _type );

		if( it_found == m_wantedIds.end() )
		{
			ProtocolMismatchException ex;
			throw ex;
		}

		for( TListWantedIdResponse::iterator
			it = it_found->second.begin(),
			it_end = it_found->second.end();
		it != it_end;
		++it )
		{
			(*it)->onServantTypeIdSuccessful( _typeId );
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void ServantFactory::getTypeIdException( const Axe::Exception & _ex, const std::string & _type )
	{
		TMapWantedIdResponse::iterator it_found = m_wantedIds.find( _type );

		if( it_found == m_wantedIds.end() )
		{
			ProtocolMismatchException ex;
			throw ex;
		}

		for( TListWantedIdResponse::iterator
			it = it_found->second.begin(),
			it_end = it_found->second.end();
		it != it_end;
		++it )
		{
			(*it)->onServantTypeIdFailed( _ex );
		}
	}
}