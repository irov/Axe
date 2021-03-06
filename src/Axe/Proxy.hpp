#	pragma once

#	include <Axe/Connection.hpp>
#	include <Axe/Response.hpp>

namespace Axe
{
	typedef AxeHandle<class ProxyConnectionProvider> ProxyConnectionProviderPtr;
	typedef AxeHandle<class Response> ResponsePtr;

	class ArchiveDispatcher;
	class ArchiveInvocation;

	class Response_Servant_destroy
		: public Response
	{
	public:
		virtual void response() = 0;

	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};

	typedef AxeHandle<class Response_Servant_destroy> Response_Servant_destroyPtr;

	class Proxy
		: virtual public AxeUtil::Shared
	{
	public:
		Proxy( std::size_t _servantId, const ProxyConnectionProviderPtr & _adaterProvider );

	public:
		std::size_t getServantId() const;
		const ProxyConnectionProviderPtr & getConnectionProvider() const;

	public:
		ArchiveInvocation & beginMessage( std::size_t _methodId, const ResponsePtr & _response );
		void processMessage();

	public:
		void destroy_async( const Response_Servant_destroyPtr & _response );

	public:
		void write( ArchiveInvocation & _ar ) const;

	protected:
		std::size_t m_servantId;
		ProxyConnectionProviderPtr m_connectionProvider;
	};

	typedef AxeHandle<Proxy> ProxyPtr;

	template<class T>
	inline T uncheckedCast( const ProxyPtr & _proxy )
	{
		std::size_t servantId = _proxy->getServantId();
		const ProxyConnectionProviderPtr & provider = _proxy->getConnectionProvider();

		typedef typename T::element_type element_type;

		return new element_type( servantId, provider );
	}

	const ProxyConnectionProviderPtr & makeProxyConnectionProvider( ArchiveDispatcher & ar, std::size_t & servantId );

	template<class T>
	T makeProxy( ArchiveDispatcher & _ar )
	{
		std::size_t servantId;

		const ProxyConnectionProviderPtr & provider = 
			makeProxyConnectionProvider( _ar, servantId );

		typedef typename T::element_type El;

		return new El( servantId, provider );
	}
}