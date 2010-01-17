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

	class CreateServantResponse
		: virtual public AxeUtil::Shared
	{
	public:
		virtual void onServantCreateSuccessful( const ServantPtr & _servant ) = 0;
		virtual void onServantCreateFailed( const ServantPtr & _servant, const Exception & _ex ) = 0;
	};

	typedef AxeHandle<CreateServantResponse> CreateServantResponsePtr;

	class Adapter
		: public Service
	{
	public:
		Adapter( const CommunicatorPtr & _communicator, const boost::asio::ip::tcp::endpoint & _endpoint, const std::string & _name, std::size_t _adapterId );

	public:
		void addServant( const ServantPtr & _servant, const CreateServantResponsePtr & _response );
		bool hasServant( std::size_t _servantId ) const;

	public:
		void setAdapterId( std::size_t _adapterId );
		std::size_t getAdapterId() const;

		void refreshServantEndpoint( std::size_t _adapterId );

	protected:
		SessionPtr makeSession() override;

	public:
		void dispatchMethod( std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const SessionPtr & _session );
		void replaceMethod( std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, ArchiveDispatcher & _archive, const SessionPtr & _session, std::size_t _adapterId );
		void exceptionMethod( std::size_t _servantId, std::size_t _requestId, const SessionPtr & _session );

	public:
		bool addServantWithId( std::size_t _servantId, const ServantPtr & _servant );

	private:
		void addServantResponse_( std::size_t _servantId, const ServantPtr & _servant, const CreateServantResponsePtr & _response );

	protected:
		CommunicatorPtr m_communicator;

		std::size_t m_adapterId;

		typedef std::map<std::size_t, ServantPtr> TMapServants;
		TMapServants m_servants;
	};

	typedef AxeHandle<Adapter> AdapterPtr;
}