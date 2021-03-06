#	include <AxeUtil/ArchiveRead.hpp>

namespace AxeUtil
{
	//////////////////////////////////////////////////////////////////////////
	ArchiveRead::ArchiveRead()
	{

	}
	//////////////////////////////////////////////////////////////////////////
	ArchiveRead::ArchiveRead( Archive & _archive )
	{
		m_archive.swap(_archive);
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
	void ArchiveRead::readArchive( Archive & _archive, std::size_t _size )
	{
		Archive::const_iterator it_begin = m_seek;
		std::advance( m_seek, _size );
		std::copy( it_begin, m_seek, _archive.begin() );
	}
	//////////////////////////////////////////////////////////////////////////
	void ArchiveRead::readArchive( Archive::iterator _it, std::size_t _size )
	{
		Archive::const_iterator it_begin = m_seek;
		std::advance( m_seek, _size );
		std::copy( it_begin, m_seek, _it );
	}
	//////////////////////////////////////////////////////////////////////////
	void ArchiveRead::readSize( std::size_t & _value )
	{
		unsigned char low_size;
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
	const AxeUtil::Archive::value_type * ArchiveRead::selectBuffer( std::size_t _size )
	{
		const AxeUtil::Archive::value_type * buff = &*m_seek;
		std::advance( m_seek, _size );
		return buff;
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
	std::size_t ArchiveRead::length( std::size_t _pos ) const
	{
		std::size_t reading = std::distance( m_archive.begin(), m_seek );
		std::size_t length = _pos - reading;
		return length;
	}
	//////////////////////////////////////////////////////////////////////////
	std::size_t ArchiveRead::rest() const
	{
		std::size_t result = std::distance( m_seek, m_archive.end() );
		return result;
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