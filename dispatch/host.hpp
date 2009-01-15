#	pragma once

class session;

class host
{
public:
	host( boost::asio::io_service & _service, const boost::asio::ip::tcp::endpoint & _endpoint );

protected:
	virtual session * make_session() = 0;

protected:
	void run();

private:
	void handle_accept( const boost::system::error_code & _ec, session * _sn );

protected:
	boost::asio::ip::tcp::acceptor m_acceptor;
};