#	pragma once

#	include "AxeUtil/Shared.hpp"

namespace Axe
{
	typedef AxeHandle<class Servant> ServantPtr;

	typedef AxeHandle<class Proxy_GridManager> Proxy_GridManagerPtr;

	class ServantFactoryGetIdResponse
		: virtual public AxeUtil::Shared
	{
	public:
		virtual void onServantTypeId( std::size_t _id ) = 0;
	};

	typedef AxeHandle<ServantFactoryGetIdResponse> ServantFactoryGetIdResponsePtr;

	class ServantGenerator
		: virtual public AxeUtil::Shared
	{
	public:
		virtual ServantPtr create() = 0;
	};

	typedef AxeHandle<ServantGenerator> ServantGeneratorPtr;

	class ServantFactory
		: virtual public AxeUtil::Shared
	{
	public:
		ServantFactory( const Proxy_GridManagerPtr & _gridManager );

	public:
		void registerServantGenerator( std::size_t _typeId, const ServantGeneratorPtr & _gen );
		ServantPtr genServant( std::size_t _typeId );

	public:
		void getTypeId( const std::string & _type, const ServantFactoryGetIdResponsePtr & _cb );

	protected:
		void provideTypeId( const std::string & _type, const ServantFactoryGetIdResponsePtr & _cb );
		void getTypeIdResponse( std::size_t _typeId, const std::string & _type );

	protected:
		typedef std::map<std::string, std::size_t> TMapIdCache;
		TMapIdCache m_ids;

		typedef std::list<ServantFactoryGetIdResponsePtr> TListWantedIdResponse;
		typedef std::map<std::string, TListWantedIdResponse> TMapWantedIdResponse;
		TMapWantedIdResponse m_wantedIds;

		typedef std::map<std::size_t, ServantGeneratorPtr> TMapServantGenerators;
		TMapServantGenerators m_generators;

		Proxy_GridManagerPtr m_gridManager;
	};

	typedef AxeHandle<ServantFactory> ServantFactoryPtr;
}