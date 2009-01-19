#	pragma once

#	include "Archive.hpp"

namespace Axe
{
	class ArchiveRead
	{
	public:
		ArchiveRead( const Archive & _archive );

	public:
		void begin();

	public:
		template<class T>
		void read_t( T & _t )
		{
			readBuffer( &_t, sizeof(T) );
		}

		void readBuffer( void * _begin, std::size_t _size );
		void readSize( std::size_t & _value );
		void readString( std::string & _value );

	public:
		void seek( std::size_t _pos );
		bool eof() const;

	protected:
		const Archive & m_archive;
		Archive::const_iterator m_seek;
	};

	void operator >> ( ArchiveRead & ar, std::string & _value );

	template<class T>
	void operator >> ( ArchiveRead & ar, T & _value )
	{
		ar.read_t( _value );
	}
}