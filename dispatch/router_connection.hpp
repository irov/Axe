#	pragma once

#	include "adapter_connection.hpp"

class router_connection;

class router_proxy_connection
	: public connection
{
public:
	router_proxy_connection( router_connection * _base, std::size_t _id );

public:
	stream_write * begin_message( std::size_t _servantId, std::size_t _methodId, response_base * _response ) override;

	void procces() override;

protected:
	router_connection * m_base;
	std::size_t m_id;
};

class router_connection
	: public adapter_connection
{
public:
	router_connection( boost::asio::io_service & _service );

public:
	void dispatch_message( std::size_t _size ) override;

protected:
	connection * get_connection( std::size_t _id );

protected:
	typedef std::map<std::size_t, router_proxy_connection *> TMapRouterConnections;
	TMapRouterConnections m_connections;
};