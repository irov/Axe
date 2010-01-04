#	pragma once

#	include <AxeUtil/Archive.hpp>

#	include <AxeProtocols/EvictorManager.hpp>

namespace Axe
{
	typedef AxeHandle<class Servant> ServantPtr;

	class ServantProviderResponse
		: virtual public AxeUtil::Shared
	{
	public:
		virtual void onServant( const ServantPtr & _servant ) = 0;
	};

	typedef AxeHandle<ServantProviderResponse> ServantProviderResponsePtr;

	class ServantProvider
		: virtual public AxeUtil::Shared
	{
	public:
		void get( std::size_t _servantId, const ServantProviderResponsePtr & _cb );

	protected:
		void onGet( const AxeUtil::Archive & _data, std::size_t _servantId );

	protected:
		typedef std::list<ServantProviderResponsePtr> TListServantProviderResponse;
		typedef std::map<std::size_t, TListServantProviderResponse> TMapWantedServant;
		TMapWantedServant m_wantedServant;

		Proxy_EvictorManagerPtr m_evictorManager;
	};	

	typedef AxeHandle<ServantProvider> ServantProviderPtr;
}