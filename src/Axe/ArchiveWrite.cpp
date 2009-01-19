#	include "ArchiveWrite.hpp"

namespace Axe
{
	//////////////////////////////////////////////////////////////////////////
	ArchiveWrite::ArchiveWrite( TBlobject & _blob )
	: m_blob(_blob)
	{
		m_begin = _blob.size();

		std::size_t size = 0;
		write_t( size );
	}
	//////////////////////////////////////////////////////////////////////////
	void ArchiveWrite::writeSize( std::size_t _size )
	{
		if( _size < 255 )
		{
			unsigned char ch_size = _size;
			write_t( ch_size );
		}
		else
		{
			unsigned char ch_size = 255;
			write_t( ch_size );
			write_t( _size );
		}	
	}
	//////////////////////////////////////////////////////////////////////////
	void ArchiveWrite::writeString( const std::string & _value )
	{
		std::size_t size = _value.size();
		const std::string::value_type * buff = _value.c_str();

		writeSize( size );
		writeBuffer( buff, buff + size );
	}
	//////////////////////////////////////////////////////////////////////////
	void ArchiveWrite::writeBuffer( const void * _begin, const void * _end )
	{
		std::size_t old_size = m_blob.size();

		m_blob.insert( m_blob.end()	
			, (const TBlobject::value_type *)_begin
			, (const TBlobject::value_type *)_end
			);

		std::size_t new_size = m_blob.size();

		*(std::size_t*)(&m_blob[m_begin]) += new_size - old_size;
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( ArchiveWrite & ar, const std::string & _value )
	{
		ar.writeString( _value );
	}
}