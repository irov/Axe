#	include <AxeUtil/ArchiveWrite.hpp>

namespace AxeUtil
{
	//////////////////////////////////////////////////////////////////////////
	void ArchiveWrite::begin()
	{
		m_begin = m_archive.size();

		std::size_t size = 0;
		write( size );
	}
	//////////////////////////////////////////////////////////////////////////
	void ArchiveWrite::writeSize( std::size_t _size )
	{
		if( _size < 255 )
		{
			unsigned char ch_size = (unsigned char)_size;
			write( ch_size );
		}
		else
		{
			unsigned char ch_size = 255;
			write( ch_size );
			write( _size );
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
	void ArchiveWrite::writeArchive( const AxeUtil::Archive::value_type * _buffer, std::size_t _size )
	{
		writeBuffer( _buffer, _buffer + _size );
	}
	//////////////////////////////////////////////////////////////////////////
	void ArchiveWrite::writeBuffer( const void * _begin, const void * _end )
	{
		std::size_t old_size = m_archive.size();

		m_archive.insert( m_archive.end()
			, (const AxeUtil::Archive::value_type *)_begin
			, (const AxeUtil::Archive::value_type *)_end
			);

		std::size_t new_size = m_archive.size();

		*(std::size_t*)(&m_archive[m_begin]) += new_size - old_size;
	}
	//////////////////////////////////////////////////////////////////////////
	const Archive & ArchiveWrite::getArchive() const
	{
		return m_archive;
	}
	//////////////////////////////////////////////////////////////////////////
	void ArchiveWrite::clear()
	{
		m_archive.clear();
	}
	//////////////////////////////////////////////////////////////////////////
	bool ArchiveWrite::empty() const
	{
		return m_archive.empty();
	}
	//////////////////////////////////////////////////////////////////////////
	void operator << ( ArchiveWrite & ar, const std::string & _value )
	{
		ar.writeString( _value );
	}
}