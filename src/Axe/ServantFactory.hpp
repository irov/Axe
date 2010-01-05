#	pragma once

#	include "AxeUtil/Shared.hpp"

namespace Axe
{
	typedef AxeHandle<class Proxy_GridManager> Proxy_GridManagerPtr;

	class ServantFactoryGetIdResponse
		: virtual public AxeUtil::Shared
	{
	public:
		virtual void onServantTypeId( std::size_t _id ) = 0;
	};

	typedef AxeHandle<ServantFactoryGetIdResponse> ServantFactoryGetIdResponsePtr;

	class ServantFactory
		: virtual public AxeUtil::Shared
	{
	public:
		ServantFactory( const Proxy_GridManagerPtr & _gridManager );

	public:
		void getTypeId( const std::string & _type, const ServantFactoryGetIdResponsePtr & _cb );

	protected:
		void provideTypeId( const std::string & _type, const ServantFactoryGetIdResponsePtr & _cb );
		void getTypeIdResponse( std::size_t _id, const std::string & _type );

	protected:
		typedef std::map<std::string, std::size_t> TMapIdCache;
		TMapIdCache m_ids;

		typedef std::list<ServantFactoryGetIdResponsePtr> TListWantedResponse;
		typedef std::map<std::string, TListWantedResponse> TMapWantedResponse;

		TMapWantedResponse m_wantedIds;

		Proxy_GridManagerPtr m_gridManager;
	};
}