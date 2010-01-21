#	pragma once

#	include "AxeUtil/Shared.hpp"

namespace Axe
{
	typedef AxeHandle<class Servant> ServantPtr;
	typedef AxeHandle<class Proxy_GridManager> Proxy_GridManagerPtr;

	class Exception;

	class ServantFactoryGenerator
		: virtual public AxeUtil::Shared
	{
	public:
		virtual ServantPtr create() = 0;
	};

	typedef AxeHandle<ServantFactoryGenerator> ServantFactoryGeneratorPtr;

	class ServantFactory
		: virtual public AxeUtil::Shared
	{
	public:
		void registerServantGenerator( const std::string & _type, const ServantFactoryGeneratorPtr & _generator );
		ServantPtr genServant( const std::string & _type ) const;

	protected:
		typedef std::map<std::string, ServantFactoryGeneratorPtr> TMapServantGenerators;
		TMapServantGenerators m_generators;
	};

	typedef AxeHandle<ServantFactory> ServantFactoryPtr;
}