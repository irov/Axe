#	include "pch.hpp"

#	include "RouterConnection.hpp"
#	include "RouterProxyConnection.hpp"

#	include "Response.hpp"

#	include "ArchiveRead.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	RouterConnection::RouterConnection( boost::asio::io_service & _service )
		: AdapterConnection( _service )
	{

	}
	//////////////////////////////////////////////////////////////////////////
	class CreateSessionResponse
		: public Response
	{
	public:
		CreateSessionResponse( const ClientPtr & _client )
			: m_client(_client)
		{
		}

	public:
		void responseCall( ArchiveRead & _ar ) override
		{

			_ar 	
		}

	protected:
		ClientPtr m_client;
	};
	//////////////////////////////////////////////////////////////////////////
	void RouterConnection::createSession( const std::string & _login, const std::string & _password, const ClientPtr & _client )
	{
		ArchiveWrite & ar = m_session->getArchiveWrite();

		ar.begin();
		
		ar << _login;
		ar << _password;
		
		std::size_t dispatchId = this->addDispatch( const ResponsePtr & _response );
	}
	//////////////////////////////////////////////////////////////////////////
	const RouterProxyConnectionPtr & RouterConnection::getConnection( std::size_t _id )
	{
		TMapRouterConnections::iterator it_found = m_connections.find( _id );

		if( it_found == m_connections.end() )
		{
			RouterProxyConnectionPtr cn = new RouterProxyConnection( this, _id );

			it_found = m_connections.insert( std::make_pair( _id, cn ) ).first;
		}

		return it_found->second;
	}
}