#	include "pch.hpp"

#	include "Grid.hpp"
#	include "GridSession.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Grid::Grid( const boost::asio::ip::tcp::endpoint & _endpoint )
		: Host(_endpoint)
		, m_enumeratorID(0)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Grid::initialize()
	{
		this->accept();
	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t Grid::addAdapter( const std::string & _adapter )
	{
		TMapAdapterIDs::const_iterator it_found = m_adapterIds.find( _adapter );

		if( it_found == m_adapterIds.end() )
		{
			it_found = 
				m_adapterIds.insert( std::make_pair( _adapter, ++m_enumeratorID ) ).first;
		}

		return it_found->second;
	}
	//////////////////////////////////////////////////////////////////////////
	SessionPtr Grid::makeSession()
	{
		GridSessionPtr session = new GridSession( m_service, this );

		return session;
	}
}
