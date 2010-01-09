#	pragma once

#	include <Axe/Connection.hpp>

namespace Axe
{
	typedef AxeHandle<class ProxyHostProvider> ProxyHostProviderPtr;
	typedef AxeHandle<class Response> ResponsePtr;

	class ArchiveDispatcher;
	class ArchiveInvocation;

	class Proxy
		: virtual public AxeUtil::Shared
	{
	public:
		Proxy( std::size_t _servantId, const ProxyHostProviderPtr & _hostProvider );

	public:
		ArchiveInvocation & beginMessage( std::size_t _methodId, const ResponsePtr & _response );
		void processMessage();

	public:
		std::size_t getServantId() const;
		const ProxyHostProviderPtr & getProxyHostProvider() const;

	public:
		void write( ArchiveInvocation & _ar ) const;

	protected:
		std::size_t m_servantId;
		ProxyHostProviderPtr m_hostProvider;
	};

	typedef AxeHandle<Proxy> ProxyPtr;

	template<class T>
	inline T uncheckedCast( const ProxyPtr & _proxy )
	{
		std::size_t servantId = _proxy->getServantId();
		const ProxyHostProviderPtr & provider = _proxy->getProxyHostProvider();

		typedef typename T::element_type element_type;

		return new element_type( servantId, provider );
	}

	const ProxyHostProviderPtr & getProxyHostProvider( ArchiveDispatcher & ar, std::size_t & servantId );

	template<class T>
	T makeProxy( ArchiveDispatcher & _ar )
	{
		std::size_t servantId;

		const ProxyHostProviderPtr & provider = 
			getProxyHostProvider( _ar, servantId );

		typedef typename T::element_type El;

		return new El( servantId, provider );
	}

	void operator << ( ArchiveInvocation & _ar, const ProxyPtr &  _value );
}