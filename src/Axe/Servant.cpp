#	include "pch.hpp"

#	include "Servant.hpp"

#	include "ArchiveWrite.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	Servant::Servant()
		: m_servantId(0)
		, m_endpointId(0)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant::setServantId( std::size_t _servantId )
	{
		m_servantId = _servantId;
	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t Servant::getServantId() const
	{
		return m_servantId;
	}
	//////////////////////////////////////////////////////////////////////////
	void Servant::setEndpointId( std::size_t _endpointId )
	{
		m_endpointId = _endpointId;
	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t Servant::getEndpointId() const
	{
		return m_endpointId;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( ArchiveWrite & ar, const ServantPtr & _value )
	{
		std::size_t servantId = _value->getServantId();
		ar.write( servantId );

		std::size_t endpointId = _value->getEndpointId();
		ar.write( endpointId );
	}
}