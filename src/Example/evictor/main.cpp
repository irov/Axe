#	include "pch.hpp"

#	include <Axe/Communicator.hpp>
#	include <Axe/ServantFactory.hpp>
#	include <Axe/Adapter.hpp>

#	include <AxeLib/EvictorManager/EvictorManager.hpp>

#	include <stdio.h>

class MyEvictorManagerGenerator
	: public ServantFactoryGenerator
{
protected:
	ServantPtr create() override
	{
		return new AxeLib::EvictorManager;
	}
};

void main()
{

	boost::property_tree::ptree pt;
	boost::property_tree::xml_parser::read_xml( "config.xml", pt );

	Axe::CommunicatorPtr cm = new Axe::Communicator( pt );

	const ServantFactoryPtr & servantFactory = cm->getServantFactory();

	servantFactory->registerServantGenerator( 
		AxeLib::EvictorManager::getTypeId()
		, new MyEvictorManagerGenerator 
		);

	boost::asio::ip::tcp::endpoint ep( boost::asio::ip::address::from_string("127.0.0.1"), 12002 );

	AdapterPtr adapter = cm->createUnregistredAdapter( ep, "EvictorAdapter" );

	adapter->addUnique( "EvictorManager", AxeLib::EvictorManager::getTypeId(), 0 );


	//cm->createGrid( ep, "Grid", grid, new MyGridCreateResponse );

	//cm->run();
}