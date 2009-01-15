#	pragma once

#	include "blobject_stream.hpp"

class stream_base
{
public:
	const TBlobject & getBuffer() const;

	bool empty() const;
	void clear();

protected:
	TBlobject m_buffer;
};

class stream_write
	: public stream_base
{
public:
	void begin();

public:
	template<class T>
	void write( T t )
	{
		write_blob( &t,  &t + 1 );
	}

	void write( const std::string & _value );
	void write_buff( TBlobject::value_type * _begin, std::size_t _size );

protected:
	void write_blob( const void * _begin, const void * _end );

protected:
	std::size_t m_begin;
};

class stream_read
	: public stream_base
{
public:
	void begin();

public:
	TBlobject::value_type * keep( std::size_t _size );

	template<class T>
	void keep_value( T ** _ptr )
	{
		TBlobject::value_type * it = keep( sizeof(T) );
		*_ptr = (T*)it;
	}

public:
	template<class T>
	void read( T & _t )
	{
		read_blob( &_t, sizeof(T) );
	}

	void read_blob( void * _begin, std::size_t _size );

	void read( std::string & _value );

	template<class T>
	void select( T ** _t )
	{
		*_t = (T*)&*m_seek;
		std::advance( m_seek, sizeof(T) );
	}

	void select( std::string ** _t );

	TBlobject::value_type * select_buff( std::size_t _size );

public:
	void assign( stream_write * _write );

public:
	void seek( std::size_t _pos );
	bool eof() const;

protected:
	TBlobject::iterator m_seek;
};