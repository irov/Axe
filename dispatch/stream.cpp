#	include "pch.hpp"

#	include "stream.hpp"

const TBlobject & stream_base::getBuffer() const
{
	return m_buffer;
}

bool stream_base::empty() const
{
	return m_buffer.empty();
}

void stream_base::clear()
{
	m_buffer.clear();
}

void stream_write::begin()
{
	m_begin = m_buffer.size();

	std::size_t size = 0;
	write( size );
}

void stream_write::write( const std::string & _value )
{
	write( _value.size() );
	write_blob( _value.c_str(), _value.c_str() + _value.size() );
}

void stream_write::write_buff( TBlobject::value_type * _begin, std::size_t _size )
{
	write_blob( _begin, _begin + _size );
}

void stream_write::write_blob( const void * _begin, const void * _end )
{
	std::size_t old_size = m_buffer.size();

	m_buffer.insert( m_buffer.end()	
		, (const TBlobject::value_type *)_begin
		, (const TBlobject::value_type *)_end
		);

	std::size_t new_size = m_buffer.size();

	*(std::size_t*)(&m_buffer[m_begin]) += new_size - old_size;
}

TBlobject::value_type * stream_read::keep( std::size_t _size )
{
	TBlobject::size_type size = m_buffer.size();
	m_buffer.resize( size + _size );

	return &m_buffer[size];
}

void stream_read::begin()
{
	m_seek = m_buffer.begin();
}

void stream_read::read_blob( void * _begin, std::size_t _size )
{
	TBlobject::iterator it_begin = m_seek;
	std::advance( m_seek, _size );
	std::copy( it_begin, m_seek, (TBlobject::value_type *)_begin );
}

void stream_read::read( std::string & _value )
{
	std::size_t size;
	read( size );

	_value.resize( size );
	read_blob( &*_value.begin(), size );
}

void stream_read::select( std::string ** _t )
{
	*_t = new std::string;
	read( **_t );
}

void stream_read::assign( stream_write * _write )
{
	const TBlobject & buff = _write->getBuffer();
	m_buffer.assign( buff.begin(), buff.end() );
}

TBlobject::value_type * stream_read::select_buff( std::size_t _size )
{
	TBlobject::value_type * buff = &*m_seek;
	seek( _size );

	return buff;
}

void stream_read::seek( std::size_t _pos )
{
	std::advance( m_seek, _pos );
}

bool stream_read::eof() const
{
	return m_seek == m_buffer.end();
}