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
	void EvictorManager::set_async( const Bellhop_EvictorManager_setPtr & _cb, std::size_t _servantId, std::size_t _typeId, const AxeUtil::Archive & _ar )
	{
		this->evict( _servantId, _typeId, _ar );

		m_servants.erase( _servantId );

		_cb->response();
	}
	//////////////////////////////////////////////////////////////////////////
	void EvictorManager::get_async( const Bellhop_EvictorManager_getPtr & _cb, std::size_t _servantId, std::size_t _hostId )
	{
		TMapServants::const_iterator it_found = m_servants.find( _servantId );

		if( it_found == m_servants.end() )
		{
			std::size_t typeId;
			AxeUtil::Archive ar;
			this->restore( _servantId, typeId, ar );

			m_servants.insert( std::make_pair(_servantId, _hostId) );

			_cb->response( ar, typeId );			
		}
		else
		{
			Axe::EvictingAlreadyRestored ear;
			ear.servantId = _servantId;
			ear.hostId = it_found->second;

			_cb->throw_exception( ear );
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void EvictorManager::makeDBID( std::string & _dbid, std::size_t _servantId ) const
	{
		char file[16];
		sprintf(file, "%9d", _servantId );

		_dbid = m_pathDB + file;
	}
	//////////////////////////////////////////////////////////////////////////
	void EvictorManager::evict( std::size_t _servantId, std::size_t _typeId, const AxeUtil::Archive & _ar )
	{
		std::string dbid;
		makeDBID( dbid, _servantId );

		FILE * f = fopen( dbid.c_str(), "wb" );

		fwrite( &_typeId, sizeof(_typeId), 1, f );

		std::size_t size;
		fwrite( &_ar[0], _ar.size(), 1, f );
	}
	//////////////////////////////////////////////////////////////////////////
	void EvictorManager::restore( std::size_t _servantId, std::size_t & _typeId, AxeUtil::Archive & _ar )
	{
		std::string dbid;
		makeDBID( dbid, _servantId );

		FILE * f = fopen( dbid.c_str(), "rb" );

		std::size_t size;
		fread( &size, sizeof(size), 1, f );

		fread( &_typeId, sizeof(_typeId), 1, f );

		_ar.resize( size );
		fread( &_ar[0], size, 1, f );
	}
}