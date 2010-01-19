#	pragma once

#	include <Axe/Connection.hpp>
#	include <Axe/Response.hpp>

namespace Axe
{
	typedef AxeHandle<class ProxyAdapterProvider> ProxyAdapterProviderPtr;
	typedef AxeHandle<class Response> ResponsePtr;

	class ArchiveDispatcher;
	class ArchiveInvocation;

	class Response_Servant_destroy
		: public Response
	{
	protected:
		virtual void response() = 0;

	public:
		void responseCall( Axe::ArchiveDispatcher & _ar, std::size_t _size ) override;
	};

	typedef AxeHandle<class Response_Servant_destroy> Response_Servant_destroyPtr;

	template<>
	class BindResponse<Response_Servant_destroyPtr>
		: public BindResponseHelper<Response_Servant_destroy, void()>
	{
	public:
		BindResponse( const TBindResponse & _response, const TBindException & _exception )
			: BindResponseHelper<Response_Servant_destroy, void()>(_response, _exception )
		{
		}

	public:
		void response() override
		{
			m_response();
		}
	};

	class Proxy
		: virtual public AxeUtil::Shared
	{
	public:
		Proxy( std::size_t _servantId, const ProxyAdapterProviderPtr & _adaterProvider );

	public:
		std::size_t getServantId() const;
		const ProxyAdapterProviderPtr & getProxyAdapterProvider() const;

	public:
		ArchiveInvocation & beginMessage( std::size_t _methodId, const ResponsePtr & _response );
		void processMessage();

	public:
		void destroy_async( const Response_Servant_destroyPtr & _response );

	public:
		void write( ArchiveInvocation & _ar ) const;

	protected:
		std::size_t m_servantId;
		ProxyAdapterProviderPtr m_adapterProvider;
	};

	typedef AxeHandle<Proxy> ProxyPtr;

	template<class T>
	inline T uncheckedCast( const ProxyPtr & _proxy )
	{
		std::size_t servantId = _proxy->getServantId();
		const ProxyAdapterProviderPtr & provider = _proxy->getProxyAdapterProvider();

		typedef typename T::element_type element_type;

		return new element_type( servantId, provider );
	}

	const ProxyAdapterProviderPtr & makeProxyAdapterProvider( ArchiveDispatcher & ar, std::size_t & servantId );

	template<class T>
	T makeProxy( ArchiveDispatcher & _ar )
	{
		std::size_t servantId;

		const ProxyAdapterProviderPtr & provider = 
			makeProxyAdapterProvider( _ar, servantId );

		typedef typename T::element_type El;

		return new El( servantId, provider );
	}

	void operator >> ( ArchiveDispatcher & _ar, ProxyPtr & _value );
	void operator << ( ArchiveInvocation & _ar, const ProxyPtr & _value );
}