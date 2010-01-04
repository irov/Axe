#	pragma once

#	include <Axe/Host.hpp>

#	include <Axe/EndpointCache.hpp>

namespace Axe
{
	typedef AxeHandle<class Communicator> CommunicatorPtr;

	typedef AxeHandle<class Adapter> AdapterPtr;

	class AdapterInitializeResponse
		: virtual public AxeUtil::Shared
	{
	public:
		virtual void onInitialize( const Axe::AdapterPtr & _adapter ) = 0;
		virtual void onFailed() = 0;
	};

	typedef AxeHandle<AdapterInitializeResponse> AdapterInitializeResponsePtr;

	class Adapter
		: public Host		
	{
	public:
		Adapter( const CommunicatorPtr & _communicator, const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name, std::size_t _hostId );

	public:
		ProxyPtr addUnique( std::size_t _servantId, const std::string & _name, const ServantPtr & _unique );

	protected:
		SessionPtr makeSession() override;

	protected:
		CommunicatorPtr m_communicator;
	};

	typedef AxeHandle<Adapter> AdapterPtr;
}