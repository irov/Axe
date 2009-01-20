#	pragma once

#	include "Archive.hpp"

#	include <string>

namespace Axe
{
	class ArchiveWrite
	{
	public:
		void begin();

	public:
		template<class T>
		void write( const T & _value )
		{
			writeBuffer( &_value,  &_value + 1 );
		}

		void writeSize( std::size_t _size );
		void writeString( const std::string & _value );
		void writeArchive( const Archive::value_type * _buffer, std::size_t _size );

	public:
		const Archive & getArchive() const;

		void clear();
		bool empty() const;

	protected:
		void writeBuffer( const void * _begin, const void * _end );

	protected:
		std::size_t m_begin;
		Archive m_archive;	
	};

	void operator << ( ArchiveWrite & ar, const std::string & _value );

	template<class T>
	void operator << ( ArchiveWrite & ar, const T & _value )
	{
		ar.write_t( _value );
	}
}