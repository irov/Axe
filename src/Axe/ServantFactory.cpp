#	include "pch.hpp"

#	include "ServantFactory.hpp"
#	include "ServantFactoryException.hpp"

#	include <AxeProtocols/GridManager.hpp>

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	void ServantFactory::registerServantGenerator( const std::string & _type, const ServantFactoryGeneratorPtr & _generator )
	{
		m_generators.insert( std::make_pair(_type, _generator) );
	}
	//////////////////////////////////////////////////////////////////////////
	ServantPtr ServantFactory::genServant( const std::string & _type ) const
	{
		TMapServantGenerators::const_iterator it_found = m_generators.find( _type );

		if( it_found == m_generators.end() )
		{
			return 0;
		}

		return it_found->second->create();
	}
}