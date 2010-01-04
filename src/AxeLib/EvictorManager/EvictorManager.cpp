#	include "pch.hpp"

#	include "EvictorManager.hpp"

#	include <stdio.h>

namespace AxeLib
{
	//////////////////////////////////////////////////////////////////////////
	EvictorManager::EvictorManager( const std::string & _pathDB )
		: m_pathDB(_pathDB)
	{

	}
	//////////////////////////////////////////////////////////////////////////
	void EvictorManager::set_async( const Bellhop_EvictorManager_setPtr & _cb, std::size_t _servantId, const AxeUtil::Archive & _ar )
	{
		std::string dbid;
		makeDBID( dbid, _servantId );

		FILE * f = fopen( dbid.c_str(), "wb" );

		std::size_t size;
		fwrite( &_ar[0], _ar.size(), 1, f );

		_cb->response();
	}
	//////////////////////////////////////////////////////////////////////////
	void EvictorManager::get_async( const Bellhop_EvictorManager_getPtr & _cb, std::size_t _servantId )
	{
		std::string dbid;
		makeDBID( dbid, _servantId );

		FILE * f = fopen( dbid.c_str(), "rb" );

		std::size_t size;
		fread( &size, sizeof(size), 1, f );

		AxeUtil::Archive ar(size);
		fread( &ar[0], size, 1, f );

		_cb->response( ar );
	}
	//////////////////////////////////////////////////////////////////////////
	void EvictorManager::makeDBID( std::string & _dbid, std::size_t _servantId ) const
	{
		char file[16];
		sprintf(file, "%9d", _servantId );

		_dbid = m_pathDB + file;
	}
}