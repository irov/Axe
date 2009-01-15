#	pragma once

#	include "host.hpp"

#	include "blobject_stream.hpp"

class communicator;
class adapter_session;
class connection;
class servant_base;

class adapter
	: public host
{
public:
	adapter( communicator * _cm, std::size_t _id, const boost::asio::ip::tcp::endpoint & _endpoint );

public:
	void initialize();

public:
	std::size_t add_servant( servant_base * _servant );
	std::size_t add_glacier( servant_base * _servant );

	void dispatch_method( std::size_t _servantId, std::size_t _methodId, std::size_t _requestId, adapter_session * _sn );

protected:
	session * make_session() override;

protected:
	communicator * m_communicator;

	std::size_t m_id;

	typedef std::map<std::size_t, servant_base *> TMapServants;
	TMapServants m_servants; 	
};