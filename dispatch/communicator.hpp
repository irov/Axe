#	pragma once

class connection;
class adapter;
class replication;

class communicator
{
public:
	communicator();

public:
	boost::asio::io_service & get_service();

public:
	void run();

public:
	adapter * add_adapter( std::size_t _adapterId, const boost::asio::ip::tcp::endpoint & _endpoint );
	connection * get_connection( const boost::asio::ip::tcp::endpoint & _endpoint );

protected:
	boost::asio::io_service m_service;

	typedef std::map<std::size_t, adapter *> TMapAdapters;
	TMapAdapters m_adapters;
	
	typedef std::map<boost::asio::ip::tcp::endpoint, connection *> TMapConnections;
	TMapConnections m_connections;
};