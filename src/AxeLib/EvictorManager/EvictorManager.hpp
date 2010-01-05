#	pragma once

#	include <AxeProtocols/EvictorManager.hpp>

namespace AxeLib
{
	using namespace Axe;

	class EvictorManager
		: public Servant_EvictorManager
	{
	public:
		EvictorManager( const std::string & _pathDB );

	public:
		void set_async( const Bellhop_EvictorManager_setPtr & _cb, std::size_t _servantId, std::size_t _typeId, const AxeUtil::Archive & _ar ) override;
		void get_async( const Bellhop_EvictorManager_getPtr & _cb, std::size_t _servantId ) override;

	protected:
		void makeDBID( std::string & _dbid, std::size_t _servantId ) const;

	protected:
		std::string m_pathDB;
	};
}