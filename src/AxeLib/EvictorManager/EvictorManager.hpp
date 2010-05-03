#	pragma once

#	include <AxeProtocols/EvictorManager.hpp>

namespace AxeLib
{
	using namespace Axe;

	class EvictorManager
		: public Servant_EvictorManager
	{
	protected:
		bool onRestore( const boost::property_tree::ptree & _pt ) override;
		void onEvict() override;

	protected:
		void create_async( const Bellhop_EvictorManager_createPtr & _cb, std::size_t _adapterId, const std::string & _typeId ) override;
		void erase_async( const Bellhop_EvictorManager_erasePtr & _cb, std::size_t _servantId ) override;

		void set_async( const Bellhop_EvictorManager_setPtr & _cb, std::size_t _servantId, const AxeUtil::Archive & _ar ) override;
		void get_async( const Bellhop_EvictorManager_getPtr & _cb, std::size_t _servantId, std::size_t _adapterId ) override;

	protected:
		void makeDBID( std::string & _dbid, std::size_t _servantId ) const;

	protected:
		void evictServant( std::size_t _servantId, std::size_t _typeId, const AxeUtil::Archive & _ar );
		bool restoreServant( std::size_t _servantId, std::size_t & _typeId, AxeUtil::Archive & _ar );
		void removeServant( std::size_t _servantId );

	protected:
		std::string m_pathDB;

		std::size_t m_enumerator;

		struct ServantDesc
		{
			std::size_t adapterId;
			std::string typeId;
		};

		typedef std::map<std::size_t, ServantDesc> TMapServants;
		TMapServants m_servants;
	};

	typedef AxeHandle<EvictorManager> EvictorManagerPtr;
}