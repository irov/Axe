#	pragma once

#	include <Axe/Communicator.hpp>

namespace Axe
{
	typedef boost::function1<void, Exception> TCommunicatorException;
	typedef boost::function1<void, AdapterPtr> TCommunicatorCreateAdapterResponse
const AdapterPtr & _adapter
	class ServerCommunicator
		: public Communicator
	{
	public:
		ServerCommunicator( const boost::property_tree::ptree & _properties );

	public:
		bool initialize();

	public:
		void createAdapter( const std::string & _name
			, const boost::asio::ip::tcp::endpoint & _endpoint
			, const TCommunicatorCreateAdapterResponse & _response
			, const TCommunicatorException & _exception 
			);

	protected:
		void createAdapterResponse( std::size_t _id
			, const boost::asio::ip::tcp::endpoint & _endpoint
			, const std::string & _name
			, const TCommunicatorCreateAdapterResponse & _response
			);

	protected:
		Proxy_GridManagerPtr m_grid;

		typedef std::map<std::string, AdapterPtr> TMapAdapters;
		TMapAdapters m_adapters;
	};
}