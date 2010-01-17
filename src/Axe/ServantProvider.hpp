#	pragma once

#	include <AxeUtil/Shared.hpp>
#	include <AxeUtil/Archive.hpp>

namespace Axe
{
	typedef AxeHandle<class Servant> ServantPtr;
	typedef AxeHandle<class ServantFactory> ServantFactoryPtr;

	typedef AxeHandle<class Proxy_EvictorManager> Proxy_EvictorManagerPtr;
	
	class Exception;

	class ServantProviderResponse
		: virtual public AxeUtil::Shared
	{
	public:
		virtual void onServant( const ServantPtr & _servant ) = 0;
		virtual void onServantReplace( std::size_t _adapterId ) = 0;
		virtual void onServantNotFound( std::size_t _servantId ) = 0;
	};

	typedef AxeHandle<ServantProviderResponse> ServantProviderResponsePtr;

	class ServantProvider
		: virtual public AxeUtil::Shared
	{
	public:
		ServantProvider( const ServantFactoryPtr & _servantFactory, const Proxy_EvictorManagerPtr & _evictorManager );

	public:
		void get( std::size_t _servantId, std::size_t _adapterId, const ServantProviderResponsePtr & _cb );

	protected:
		void onGet( const AxeUtil::Archive & _data, std::size_t _typeId, std::size_t _servantId );
		void onException( const Exception & _ex, std::size_t _servantId );

	protected:
		typedef std::list<ServantProviderResponsePtr> TListServantProviderResponse;
		typedef std::map<std::size_t, TListServantProviderResponse> TMapWantedServant;
		TMapWantedServant m_wantedServant;

		ServantFactoryPtr m_servantFactory;
		Proxy_EvictorManagerPtr m_evictorManager;
	};	

	typedef AxeHandle<ServantProvider> ServantProviderPtr;
}