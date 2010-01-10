#	pragma once

#	include <Axe/Service.hpp>
#	include <Axe/ServantProvider.hpp>

namespace Axe
{
	typedef AxeHandle<class Session> SessionPtr;
	typedef AxeHandle<class Servant> ServantPtr;
	typedef AxeHandle<class Proxy> ProxyPtr;
	typedef AxeHandle<class Communicator> CommunicatorPtr;

	class ArchiveDispatcher;

	class Host
		: public Service
	{
	public:
		Host( const CommunicatorPtr & _communicator, const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name, std::size_t _hostId );

	public:
		ProxyPtr addServant( std::size_t _servantId, const ServantPtr & _servant );
		bool hasServant( std::size_t _servantId ) const;

	public:
		void setHostId( std::size_t _hostId );
		std::size_t getHostId() const;

		void refreshServantEndpoint( std::size_t _hostId );

	public:
		void dispatchMethod( std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const SessionPtr & _session );
		void replaceMethod( std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const SessionPtr & _session, std::size_t _hostId );
		void exceptionMethod( std::size_t _servantId, std::size_t _requestId, const SessionPtr & _session );

	protected:
		CommunicatorPtr m_communicator;

		std::size_t m_hostId;

		typedef std::map<std::size_t, ServantPtr> TMapServants;
		TMapServants m_servants;
	};

	typedef AxeHandle<Host> HostPtr;
}