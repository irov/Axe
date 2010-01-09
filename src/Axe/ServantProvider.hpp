#	pragma once

#	include <AxeUtil/Shared.hpp>
#	include <AxeUtil/Archive.hpp>

namespace Axe
{
	typedef AxeHandle<class Servant> ServantPtr;
	typedef AxeHandle<class ServantFactory> ServantFactoryPtr;

	typedef AxeHandle<class Proxy_EvictorManager> Proxy_EvictorManagerPtr;

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
		ServantProvider( const ServantFactoryPtr & _servantFactory );

	public:
		void get( std::size_t _servantId, std::size_t _hostId, const ServantProviderResponsePtr & _cb );

	protected:
		void onGet( const AxeUtil::Archive & _data, std::size_t _typeId, std::size_t _servantId );

	protected:
		typedef std::list<ServantProviderResponsePtr> TListServantProviderResponse;
		typedef std::map<std::size_t, TListServantProviderResponse> TMapWantedServant;
		TMapWantedServant m_wantedServant;

		ServantFactoryPtr m_servantFactory;
		Proxy_EvictorManagerPtr m_evictorManager;
	};	

	typedef AxeHandle<ServantProvider> ServantProviderPtr;
}