#	include "pch.hpp"

#	include "EvictorManager.hpp"

#	include <stdio.h>

namespace AxeLib
{
	//////////////////////////////////////////////////////////////////////////
	bool EvictorManager::onRestore( const boost::property_tree::ptree & _pt )
	{
		m_pathDB = pt.get<std::string>("PathDB");

		FILE * f = fopen( m_pathDB.c_str(), "rb" );

		if( f == 0 )
		{
			f = fopen( m_pathDB.c_str(), "rw" );

			m_enumerator = 0;

			fwrite( &m_enumerator, sizeof(m_enumerator), 1, f );

			fclose( f );
		}
		else
		{
			fread( &m_enumerator, sizeof(m_enumerator), 1, f );
	
			fclose( f );
		}

		return true;
	}
	//////////////////////////////////////////////////////////////////////////
	void EvictorManager::onEvict()
	{
		FILE * f = fopen( m_pathDB.c_str(), "rw" );

		fwrite( &m_enumerator, sizeof(m_enumerator), 1, f );

		fclose( f );
	}
	//////////////////////////////////////////////////////////////////////////
	void EvictorManager::create_async( const Bellhop_EvictorManager_createPtr & _cb, std::size_t _adapterId, const std::string & _typeId )
	{
		++m_enumerator;

		ServantDesc desc;
		desc.adapterId = _adapterId;
		desc.typeId = _typeId;

		m_servants.insert( std::make_pair( m_enumerator, desc ) );

		_cb->response( m_enumerator );
	}
	//////////////////////////////////////////////////////////////////////////
	void EvictorManager::erase_async( const Bellhop_EvictorManager_erasePtr & _cb, std::size_t _servantId )
	{
		TMapServants::const_iterator it_found = m_servants.find( _servantId );

		if( it_found == m_servants.end() )
		{
			Axe::EvictorNotFoundException ex;
			ex.servantId = _servantId;

			_cb->throw_exception( ex );
			return;
		}

		removeServant( _servantId );

		m_servants.erase( it_found );

		_cb->response();
	}
	//////////////////////////////////////////////////////////////////////////
	void EvictorManager::set_async( const Bellhop_EvictorManager_setPtr & _cb, std::size_t _servantId, const AxeUtil::Archive & _ar )
	{
		this->evictServant( _servantId, _typeId, _ar );

		m_servants.erase( _servantId );

		_cb->response();
	}
	//////////////////////////////////////////////////////////////////////////
	void EvictorManager::get_async( const Bellhop_EvictorManager_getPtr & _cb, std::size_t _servantId, std::size_t _adapterId )
	{
		TMapServants::const_iterator it_found = m_servants.find( _servantId );

		if( it_found == m_servants.end() )
		{
			std::size_t typeId;
			AxeUtil::Archive ar;
			
			if( this->restoreServant( _servantId, typeId, ar ) == true )
			{
				m_servants.insert( std::make_pair(_servantId, _adapterId) );

				_cb->response( ar, typeId );
			}
			else
			{
				Axe::EvictorNotFoundException ex;
				ex.servantId = _servantId;

				_cb->throw_exception( ex );
			}
		}
		else
		{
			Axe::EvictorAlreadyRestored ear;
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
	void EvictorManager::evictServant( std::size_t _servantId, std::size_t _typeId, const AxeUtil::Archive & _ar )
	{
		std::string dbid;
		makeDBID( dbid, _servantId );

		FILE * f = fopen( dbid.c_str(), "wb" );

		if( f == 0 )
		{
			return;
		}

		fwrite( &_typeId, sizeof(_typeId), 1, f );

		std::size_t size;
		fwrite( &_ar[0], _ar.size(), 1, f );

		fclose( f );
	}
	//////////////////////////////////////////////////////////////////////////
	bool EvictorManager::restoreServant( std::size_t _servantId, std::size_t & _typeId, AxeUtil::Archive & _ar )
	{
		std::string dbid;
		makeDBID( dbid, _servantId );

		FILE * f = fopen( dbid.c_str(), "rb" );

		if( f == 0 )
		{
			return false;
		}

		std::size_t size;
		fread( &size, sizeof(size), 1, f );

		fread( &_typeId, sizeof(_typeId), 1, f );

		_ar.resize( size );
		fread( &_ar[0], size, 1, f );

		fclose( f );

		return true;
	}
	//////////////////////////////////////////////////////////////////////////
	void EvictorManager::removeServant( std::size_t _servantId )
	{
		
	}
}