#	pragma once

#	include "host.hpp"
#	include "response_base.hpp"

class router_session;

class router_response
	: public response_base
{
public:
	router_response( std::size_t _requestId, router_session * _sn );

public:
	void response_call( stream_read * _cn ) override;

protected:
	std::size_t m_requestId;
	router_session * m_session;
};

class connection;

class router
	: public host
{
public:
	router( boost::asio::io_service & _service, const boost::asio::ip::tcp::endpoint & _endpoint );

public:
	void initialize();
	
public:
	void dispatch_method( std::size_t _sizeArgs, std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, std::size_t _endpointId, router_session * _sn );

protected:
	session * make_session() override;

protected:
	typedef std::map<std::size_t, connection *> TMapRouming;
	TMapRouming m_rouming;
};