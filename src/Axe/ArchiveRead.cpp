#	include "pch.hpp"
#	include "ArchiveRead.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	ArchiveRead::ArchiveRead( const ConnectionCachePtr & _connectionCache )
		: m_connectionCache(_connectionCache)
	{

	}
	//////////////////////////////////////////////////////////////////////////
	void ArchiveRead::begin()
	{
		m_seek = m_archive.begin();
	}
	//////////////////////////////////////////////////////////////////////////
	void ArchiveRead::readBuffer( void * _begin, std::size_t _size )
	{
		Archive::const_iterator it_begin = m_seek;
		std::advance( m_seek, _size );
		std::copy( it_begin, m_seek, (Archive::value_type *)_begin );
	}
	//////////////////////////////////////////////////////////////////////////
	void ArchiveRead::readSize( std::size_t & _value )
	{
		char low_size;
		read( low_size );

		if( low_size == 255 )
		{
			read( _value );
		}
		else
		{
			_value = low_size;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void ArchiveRead::readString( std::string & _value )
	{
		std::size_t size;
		readSize( size );

		_value.resize( size );
		readBuffer( &*_value.begin(), size );
	}
	//////////////////////////////////////////////////////////////////////////
	const Archive::value_type * ArchiveRead::selectBuffer( std::size_t _size )
	{
		std::advance( m_seek, _size );
		return &*m_seek;
	}
	//////////////////////////////////////////////////////////////////////////
	Archive::value_type * ArchiveRead::keepBuffer( std::size_t _size )
	{
		if( _size == 0 )
		{
			return 0;
		}

		Archive::size_type size = m_archive.size();

		m_archive.resize( size + _size );

		return &m_archive[size];
	}
	//////////////////////////////////////////////////////////////////////////
	void ArchiveRead::clear()
	{
		m_archive.clear();
	}
	//////////////////////////////////////////////////////////////////////////
	void ArchiveRead::seek( std::size_t _pos )
	{
		std::advance( m_seek, _pos );
	}
	//////////////////////////////////////////////////////////////////////////
	bool ArchiveRead::eof() const
	{
		return m_seek == m_archive.end();
	}
	//////////////////////////////////////////////////////////////////////////
	void operator >> ( ArchiveRead & ar, std::string & _value )
	{
		ar.readString( _value );
	}
	//////////////////////////////////////////////////////////////////////////
	const ConnectionCachePtr & ArchiveRead::getConnectionCache() const
	{
		return m_connectionCache;
	}
}