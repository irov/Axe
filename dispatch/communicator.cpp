#	include "pch.hpp"

#	include "communicator.hpp"
#	include "adapter.hpp"

#	include "adapter_connection.hpp"

communicator::communicator()
{}

boost::asio::io_service & communicator::get_service()
{
	return m_service;
}

void communicator::run()
{
	m_service.run();
}

adapter * communicator::add_adapter( std::size_t _adapterId, const boost::asio::ip::tcp::endpoint & _endpoint )
{
	adapter * ad = new adapter( this, _adapterId, _endpoint );

	connection * cn  = this->get_connection( _endpoint );

	m_connections.insert( std::make_pair( _endpoint, cn ) );
	m_adapters.insert( std::make_pair( _adapterId, ad ) );

	return ad;
}

connection * communicator::get_connection( const boost::asio::ip::tcp::endpoint & _endpoint )
{
	TMapConnections::iterator it_found = m_connections.find( _endpoint );

	if( it_found == m_connections.end() )
	{
		adapter_connection * cn = new adapter_connection( m_service );

		cn->connect( _endpoint );

		it_found = 
			m_connections.insert( std::make_pair( _endpoint, cn ) ).first;
	}

	return it_found->second;
}