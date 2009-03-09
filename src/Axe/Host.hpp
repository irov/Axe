#	pragma once

#	include "Service.hpp"
#	include "Proxy.hpp"

#	include "ConnectionCache.hpp"

namespace Axe
{
	typedef AxeHandle<class Session> SessionPtr;
	typedef AxeHandle<class Servant> ServantPtr;
	typedef AxeHandle<class Connection> ConnectionPtr;

	class Host
		: public Service
	{
	public:
		Host( boost::asio::io_service & _service, const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name );

	public:
		void setHostId( std::size_t _hostId );
		std::size_t getHostId() const;

	public:
		void dispatchMethod( std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, const SessionPtr & _session );

	protected:
		bool addServantByID( const ServantPtr & _servant );

	protected:
		typedef std::map<std::size_t, ServantPtr> TMapServants;
		TMapServants m_servants;
	};

	typedef AxeHandle<Host> HostPtr;
}