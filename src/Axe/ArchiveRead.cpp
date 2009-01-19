#	include "ArchiveRead.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	ArchiveRead::ArchiveRead( const Archive & _archive )
		: m_archive(_archive)
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
		read_t( low_size );

		if( low_size == 255 )
		{
			read_t( _value );
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
}